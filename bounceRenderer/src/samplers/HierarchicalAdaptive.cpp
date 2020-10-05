//
// Created by Thomas Vallentin on 01/09/2020.
//

#include "samplers/HierarchicalAdaptive.hpp"

void HierarchicalAdaptive::initialize(RayTracer *tracer) {
    raytracer = tracer;

    width = tracer->camera().width();
    height = tracer->camera().height();

    size_t pixelCount = width * height * 3;

    for (size_t i = 0; i < pixelCount; i++)
        buffer.emplace_back(0.0f);  // Fill the buffer with black

    // initialize first block containing the whole image
    currentBlock = new Block(0, 0,
                             width / 2, height / 2);
    blocks.push(new Block(0, height / 2,
                          width / 2, height));
    blocks.push(new Block(width / 2, 0,
                          width, height / 2));
    blocks.push(new Block(width / 2, height / 2,
                          width, height));

    splitThreshold = 256 * threshold;
}


bool HierarchicalAdaptive::sampleRay(unsigned int &u, unsigned int &v, Ray &ray) {
    // Get lock to ensure no other thread will be splitting at the same time
    {
        std::unique_lock<std::mutex> lock(sampleLock);

        x++;

        if (x >= currentBlock->xMax) {
            // End of a row of pixel of the current block, reset x, increment y
            x = int(currentBlock->xMin);
            y++;

            if (y >= currentBlock->yMax) {
                if (raytracer->sampleBuffer[v * width + u] < raytracer->minSamples()) {
                    // We haven't reach the min samples, keep tracing without checking for errors
                    blocks.push(currentBlock);
                } else {
                    // We reached the end of the current block, compute its error
                    float error = computeError(currentBlock);

                    Block *b1, *b2;

                    if (error < splitThreshold) {
                        if (error > threshold) {
                            // Error is small but not small enough for the global threshold. Splitting the block
                            if (currentBlock->width < 16 || currentBlock->height < 16) {
                                blocks.push(currentBlock);

                            } else {

                                if (currentBlock->width >= currentBlock->height) {
                                    // Split on th x axis
                                    b1 = new Block(currentBlock->xMin, currentBlock->yMin,
                                                   currentBlock->xMin + currentBlock->width / 2, currentBlock->yMax);
                                    b2 = new Block(currentBlock->xMin + currentBlock->width / 2, currentBlock->yMin,
                                                   currentBlock->xMax, currentBlock->yMax);

                                } else {
                                    // Split on the y axis
                                    b1 = new Block(currentBlock->xMin, currentBlock->yMin,
                                                   currentBlock->xMax, currentBlock->yMin + currentBlock->height / 2);
                                    b2 = new Block(currentBlock->xMin, currentBlock->yMin + currentBlock->height / 2,
                                                   currentBlock->xMax, currentBlock->yMax);
                                }
                                // Add the new block to the queue
                                blocks.push(b1);
                                blocks.push(b2);
                            }
                        } else {
//                            std::cout << "Error is small enough, stop sampling" << std::endl;

                            if (blocks.empty())
                                return false;
                        }

                    } else {
                        // The error is still too big, re-schedule the block at the end of th queue
                        blocks.push(currentBlock);
                    }
                }

                currentBlock = blocks.front();
                blocks.pop();
                x = int(currentBlock->xMin);
                y = int(currentBlock->yMin);
            }
        }

        if (raytracer->sampleBuffer[y * width + x] >= raytracer->maxSamples()) {
            return false;
        }
        // filling the ray with the data
        sampleCamera(ray);
        u = x;
        v = y;
    }

    return true;
}

float HierarchicalAdaptive::computeError(Block *block) {
    float error = 0.0f, pixelError, blockPixelCount, ir, ig, ib, rn;
    unsigned int colorIndex;

    for (size_t v = block->yMin; v < block->yMax; v++) {

        for (size_t u = block->xMin; u < block->xMax; u++) {
            colorIndex = (v * width + u) * 3;
            ir = raytracer->pixelBuffer[colorIndex];
            ig = raytracer->pixelBuffer[colorIndex + 1];
            ib = raytracer->pixelBuffer[colorIndex + 2];

            if (ir == 0 && ig == 0 && ib == 0)
                continue;

            pixelError = std::abs(ir - buffer[colorIndex]);
            pixelError += std::abs(ig - buffer[colorIndex + 1]);
            pixelError += std::abs(ib - buffer[colorIndex + 2]);
            pixelError /= std::sqrt(ir + ig + ib);

            error += pixelError;
        }
    }
    blockPixelCount = float(block->width * block->height);
    rn = std::sqrt(blockPixelCount / float(width * height)) / blockPixelCount;

    return error * rn;
}

void HierarchicalAdaptive::update(const unsigned int &u, const unsigned int &v, const Color &color) {
    unsigned int sampleIndex = v * width + u;
    unsigned int currentSample = raytracer->sampleBuffer[sampleIndex];
    if (u == 15 && v == 25)

    // Storing only the even samples. Return if sample is odd.
    if (currentSample % 2)
        return;

    // Divide the current sample by two since we only take one sample over 2
    currentSample /= 2;

    unsigned int colorIndex = sampleIndex * 3;

    buffer[colorIndex] = (buffer[colorIndex] * float(currentSample) + color.r) / float(currentSample + 1);
    buffer[colorIndex + 1] = (buffer[colorIndex + 1] * float(currentSample) + color.g) / float(currentSample + 1);
    buffer[colorIndex + 2] = (buffer[colorIndex + 2] * float(currentSample) + color.b) / float(currentSample + 1);
}

void HierarchicalAdaptive::sampleCamera(Ray &ray) {
    // Sampling the camera using a very simple random sampling
    float urand = randomFlt();
    float vrand = randomFlt();
    float u = (float(x) + urand) / float(width);
    float v = (float(y) + vrand) / float(height);

    raytracer->camera().generateRay(u, v, ray);
}

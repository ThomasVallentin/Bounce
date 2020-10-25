#include "core/Shape.hpp"

HitData Shape::sampleFromPoint(const HitData &from, float &pdf) const {
    HitData sampled = sample(pdf);

    Vector3 wi = (from.position - sampled.position).normalized();

    float cosTheta = std::abs(dot(sampled.normal, wi));
    if (cosTheta == 0)
        pdf = 0;
    else
        pdf /= cosTheta;

    return sampled;
}

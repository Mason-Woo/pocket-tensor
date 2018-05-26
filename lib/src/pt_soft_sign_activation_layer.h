﻿/*
 * pocket-tensor (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 * Kerasify (c) 2016 Robert W. Rose
 *
 * MIT License, see LICENSE file.
 */

#ifndef PT_SOFT_SIGN_ACTIVATION_LAYER_H
#define PT_SOFT_SIGN_ACTIVATION_LAYER_H

#include "pt_tensor.h"
#include "pt_activation_layer.h"

namespace pt
{

class SoftSignActivationLayer : public ActivationLayer
{

public:
    using ActivationLayer::apply;

    SoftSignActivationLayer() = default;

    void apply(const Config&, Tensor& out) const final
    {
        // return x / (1.f + std::abs(x));

        Tensor::Vector one = makeVector(FloatType(1));

        for(auto it = out.begin(), end = out.end(); it != end; it += Tensor::VectorSize)
        {
            auto ptr = &*it;
            Tensor::Vector v = simdpp::load(ptr);
            Tensor::Vector d = simdpp::add(one, simdpp::abs(v));
            simdpp::store(ptr, simdpp::div(v, d));
        }
    }
};

}

#endif

﻿/*
 * pocket-tensor (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 * Kerasify (c) 2016 Robert W. Rose
 *
 * MIT License, see LICENSE file.
 */

#include "pt_elu_layer.h"

#include "pt_tensor.h"
#include "pt_parser.h"

namespace pt
{

std::unique_ptr<EluLayer> EluLayer::create(std::istream& stream)
{
    float alpha = 0;

    if(! Parser::parse(stream, alpha))
    {
        PT_LOG_ERROR << "Alpha parse failed" << std::endl;
        return std::unique_ptr<EluLayer>();
    }

    return std::unique_ptr<EluLayer>(new EluLayer(FloatType(alpha)));
}

bool EluLayer::apply(const Config&, Tensor&& in, Tensor& out) const
{
    out = std::move(in);

    for(FloatType& value : out)
    {
        if(value < 0)
        {
            value = _alpha * std::expm1(value);
        }
    }

    return true;
}

EluLayer::EluLayer(FloatType alpha) noexcept :
    _alpha(alpha)
{
}

}

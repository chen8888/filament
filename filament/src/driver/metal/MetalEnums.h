/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TNT_FILAMENT_DRIVER_METALENUMS_H
#define TNT_FILAMENT_DRIVER_METALENUMS_H

#include "driver/Driver.h"

#include <Metal/Metal.h>

#include <utils/Panic.h>

namespace filament {
namespace driver {

static inline MTLCompareFunction getMetalCompareFunction(Driver::RasterState::DepthFunc func) {
    switch (func) {
        case Driver::RasterState::DepthFunc::LE:
            return MTLCompareFunctionLessEqual;
        case Driver::RasterState::DepthFunc::GE:
            return MTLCompareFunctionGreaterEqual;
        case Driver::RasterState::DepthFunc::L:
            return MTLCompareFunctionLess;
        case Driver::RasterState::DepthFunc::G:
            return MTLCompareFunctionGreater;
        case Driver::RasterState::DepthFunc::E:
            return MTLCompareFunctionEqual;
        case Driver::RasterState::DepthFunc::NE:
            return MTLCompareFunctionNotEqual;
        case Driver::RasterState::DepthFunc::A:
            return MTLCompareFunctionAlways;
        case Driver::RasterState::DepthFunc::N:
            return MTLCompareFunctionNever;
    }
}

static inline MTLIndexType getIndexType(size_t elementSize) {
    if (elementSize == 2) {
        return MTLIndexTypeUInt16;
    } else if (elementSize == 4) {
        return MTLIndexTypeUInt32;
    }
    ASSERT_POSTCONDITION(false, "Index element size not supported.");
}

static inline MTLVertexFormat getMetalFormat(ElementType type, bool normalized) {
    if (normalized) {
        switch (type) {
            // Single Component Types
            case ElementType::BYTE: return MTLVertexFormatCharNormalized;
            case ElementType::UBYTE: return MTLVertexFormatUCharNormalized;
            case ElementType::SHORT: return MTLVertexFormatShortNormalized;
            case ElementType::USHORT: return MTLVertexFormatUShortNormalized;
                // Two Component Types
            case ElementType::BYTE2: return MTLVertexFormatChar2Normalized;
            case ElementType::UBYTE2: return MTLVertexFormatUChar2Normalized;
            case ElementType::SHORT2: return MTLVertexFormatShort2Normalized;
            case ElementType::USHORT2: return MTLVertexFormatUShort2Normalized;
                // Three Component Types
            case ElementType::BYTE3: return MTLVertexFormatChar3Normalized;
            case ElementType::UBYTE3: return MTLVertexFormatUChar3Normalized;
            case ElementType::SHORT3: return MTLVertexFormatShort3Normalized;
            case ElementType::USHORT3: return MTLVertexFormatUShort3Normalized;
                // Four Component Types
            case ElementType::BYTE4: return MTLVertexFormatChar4Normalized;
            case ElementType::UBYTE4: return MTLVertexFormatUChar4Normalized;
            case ElementType::SHORT4: return MTLVertexFormatShort4Normalized;
            case ElementType::USHORT4: return MTLVertexFormatUShort4Normalized;
            default:
                ASSERT_POSTCONDITION(false, "Normalized format does not exist.");
                return MTLVertexFormatInvalid;
        }
    }
    switch (type) {
        // Single Component Types
        case ElementType::BYTE: return MTLVertexFormatChar;
        case ElementType::UBYTE: return MTLVertexFormatUChar;
        case ElementType::SHORT: return MTLVertexFormatShort;
        case ElementType::USHORT: return MTLVertexFormatUShort;
        case ElementType::HALF: return MTLVertexFormatHalf;
        case ElementType::INT: return MTLVertexFormatInt;
        case ElementType::UINT: return MTLVertexFormatUInt;
        case ElementType::FLOAT: return MTLVertexFormatFloat;
            // Two Component Types
        case ElementType::BYTE2: return MTLVertexFormatChar2;
        case ElementType::UBYTE2: return MTLVertexFormatUChar2;
        case ElementType::SHORT2: return MTLVertexFormatShort2;
        case ElementType::USHORT2: return MTLVertexFormatUShort2;
        case ElementType::HALF2: return MTLVertexFormatHalf2;
        case ElementType::FLOAT2: return MTLVertexFormatFloat2;
            // Three Component Types
        case ElementType::BYTE3: return MTLVertexFormatChar3;
        case ElementType::UBYTE3: return MTLVertexFormatUChar3;
        case ElementType::SHORT3: return MTLVertexFormatShort3;
        case ElementType::USHORT3: return MTLVertexFormatUShort3;
        case ElementType::HALF3: return MTLVertexFormatHalf3;
        case ElementType::FLOAT3: return MTLVertexFormatFloat3;
            // Four Component Types
        case ElementType::BYTE4: return MTLVertexFormatChar4;
        case ElementType::UBYTE4: return MTLVertexFormatUChar4;
        case ElementType::SHORT4: return MTLVertexFormatShort4;
        case ElementType::USHORT4: return MTLVertexFormatUShort4;
        case ElementType::HALF4: return MTLVertexFormatHalf4;
        case ElementType::FLOAT4: return MTLVertexFormatFloat4;
    }
    return MTLVertexFormatInvalid;
}

static constexpr MTLPixelFormat getMetalFormat(TextureFormat format) {
    switch (format) {
        // 8-bits per element
        case TextureFormat::R8: return MTLPixelFormatR8Unorm;
        case TextureFormat::R8_SNORM: return MTLPixelFormatR8Snorm;
        case TextureFormat::R8UI: return MTLPixelFormatR8Uint;
        case TextureFormat::R8I: return MTLPixelFormatR8Sint;
        case TextureFormat::STENCIL8: return MTLPixelFormatStencil8;

        // 16-bits per element
        case TextureFormat::R16F: return MTLPixelFormatR16Float;
        case TextureFormat::R16UI: return MTLPixelFormatR16Uint;
        case TextureFormat::R16I: return MTLPixelFormatR16Sint;
        case TextureFormat::RG8: return MTLPixelFormatRG8Unorm;
        case TextureFormat::RG8_SNORM: return MTLPixelFormatRG8Snorm;
        case TextureFormat::RG8UI: return MTLPixelFormatRG8Uint;
        case TextureFormat::RG8I: return MTLPixelFormatRG8Sint;

        case TextureFormat::DEPTH16: return MTLPixelFormatDepth16Unorm;

        // todo: packed 16 bit formats are only available on iOS
        // Metal: add all texture formats.
        case TextureFormat::RGB565:
        case TextureFormat::RGB5_A1:
        case TextureFormat::RGBA4:
            return MTLPixelFormatInvalid;

        // 24-bits per element, not supported by Metal.
        case TextureFormat::RGB8:
        case TextureFormat::SRGB8:
        case TextureFormat::RGB8_SNORM:
        case TextureFormat::RGB8UI:
        case TextureFormat::RGB8I:
        case TextureFormat::DEPTH24:
            return MTLPixelFormatInvalid;

        // 32-bits per element
        case TextureFormat::R32F: return MTLPixelFormatR32Float;
        case TextureFormat::R32UI: return MTLPixelFormatR32Uint;
        case TextureFormat::R32I: return MTLPixelFormatR32Sint;
        case TextureFormat::RG16F: return MTLPixelFormatRG16Float;
        case TextureFormat::RG16UI: return MTLPixelFormatRG16Uint;
        case TextureFormat::RG16I: return MTLPixelFormatRG16Sint;
        case TextureFormat::R11F_G11F_B10F: return MTLPixelFormatRG11B10Float;
        case TextureFormat::RGB9_E5: return MTLPixelFormatRGB9E5Float;
        case TextureFormat::RGBA8: return MTLPixelFormatRGBA8Unorm;
        case TextureFormat::SRGB8_A8: return MTLPixelFormatRGBA8Unorm_sRGB;
        case TextureFormat::RGBA8_SNORM: return MTLPixelFormatRGBA8Snorm;
        case TextureFormat::RGB10_A2: return MTLPixelFormatRGB10A2Unorm;
        case TextureFormat::RGBA8UI: return MTLPixelFormatRGBA8Uint;
        case TextureFormat::RGBA8I: return MTLPixelFormatRGBA8Sint;
        case TextureFormat::DEPTH32F: return MTLPixelFormatDepth32Float;
        case TextureFormat::DEPTH24_STENCIL8: return MTLPixelFormatDepth24Unorm_Stencil8;
        case TextureFormat::DEPTH32F_STENCIL8: return MTLPixelFormatDepth32Float_Stencil8;

        // 48-bits per element
        case TextureFormat::RGB16F:
        case TextureFormat::RGB16UI:
        case TextureFormat::RGB16I:
            return MTLPixelFormatInvalid;

        // 64-bits per element
        case TextureFormat::RG32F: return MTLPixelFormatRG32Float;
        case TextureFormat::RG32UI: return MTLPixelFormatRG32Uint;
        case TextureFormat::RG32I: return MTLPixelFormatRG32Sint;
        case TextureFormat::RGBA16F: return MTLPixelFormatRGBA16Float;
        case TextureFormat::RGBA16UI: return MTLPixelFormatRGBA16Uint;
        case TextureFormat::RGBA16I: return MTLPixelFormatRGBA16Sint;

        // 96-bits per element
        case TextureFormat::RGB32F:
        case TextureFormat::RGB32UI:
        case TextureFormat::RGB32I:
            return MTLPixelFormatInvalid;

        // 128-bits per element
        case TextureFormat::RGBA32F: return MTLPixelFormatRGBA32Float;
        case TextureFormat::RGBA32UI: return MTLPixelFormatRGBA32Uint;
        case TextureFormat::RGBA32I: return MTLPixelFormatRGBA32Sint;

        // compressed formats

        case TextureFormat::EAC_R11:
        case TextureFormat::EAC_R11_SIGNED:
        case TextureFormat::EAC_RG11:
        case TextureFormat::EAC_RG11_SIGNED:
        case TextureFormat::ETC2_RGB8:
        case TextureFormat::ETC2_SRGB8:
        case TextureFormat::ETC2_RGB8_A1:
        case TextureFormat::ETC2_SRGB8_A1:
        case TextureFormat::ETC2_EAC_RGBA8:
        case TextureFormat::ETC2_EAC_SRGBA8:

        case TextureFormat::DXT1_RGB:
        case TextureFormat::DXT1_RGBA:
        case TextureFormat::DXT3_RGBA:
        case TextureFormat::DXT5_RGBA:

        case TextureFormat::RGBA_ASTC_4x4:
        case TextureFormat::RGBA_ASTC_5x4:
        case TextureFormat::RGBA_ASTC_5x5:
        case TextureFormat::RGBA_ASTC_6x5:
        case TextureFormat::RGBA_ASTC_6x6:
        case TextureFormat::RGBA_ASTC_8x5:
        case TextureFormat::RGBA_ASTC_8x6:
        case TextureFormat::RGBA_ASTC_8x8:
        case TextureFormat::RGBA_ASTC_10x5:
        case TextureFormat::RGBA_ASTC_10x6:
        case TextureFormat::RGBA_ASTC_10x8:
        case TextureFormat::RGBA_ASTC_10x10:
        case TextureFormat::RGBA_ASTC_12x10:
        case TextureFormat::RGBA_ASTC_12x12:
        case TextureFormat::SRGB8_ALPHA8_ASTC_4x4:
        case TextureFormat::SRGB8_ALPHA8_ASTC_5x4:
        case TextureFormat::SRGB8_ALPHA8_ASTC_5x5:
        case TextureFormat::SRGB8_ALPHA8_ASTC_6x5:
        case TextureFormat::SRGB8_ALPHA8_ASTC_6x6:
        case TextureFormat::SRGB8_ALPHA8_ASTC_8x5:
        case TextureFormat::SRGB8_ALPHA8_ASTC_8x6:
        case TextureFormat::SRGB8_ALPHA8_ASTC_8x8:
        case TextureFormat::SRGB8_ALPHA8_ASTC_10x5:
        case TextureFormat::SRGB8_ALPHA8_ASTC_10x6:
        case TextureFormat::SRGB8_ALPHA8_ASTC_10x8:
        case TextureFormat::SRGB8_ALPHA8_ASTC_10x10:
        case TextureFormat::SRGB8_ALPHA8_ASTC_12x10:
        case TextureFormat::SRGB8_ALPHA8_ASTC_12x12:

        default:
        case TextureFormat::UNUSED:
            return MTLPixelFormatInvalid;
    }
}

static inline MTLBlendOperation getMetalBlendOperation(BlendEquation equation) {
    switch (equation) {
        case BlendEquation::ADD: return MTLBlendOperationAdd;
        case BlendEquation::SUBTRACT: return MTLBlendOperationSubtract;
        case BlendEquation::REVERSE_SUBTRACT: return MTLBlendOperationReverseSubtract;
        case BlendEquation::MIN: return MTLBlendOperationMin;
        case BlendEquation::MAX: return MTLBlendOperationMax;
    }
}

static inline MTLBlendFactor getMetalBlendFactor(BlendFunction function) {
    switch (function) {
        case BlendFunction::ZERO: return MTLBlendFactorZero;
        case BlendFunction::ONE: return MTLBlendFactorOne;
        case BlendFunction::SRC_COLOR: return MTLBlendFactorSourceColor;
        case BlendFunction::ONE_MINUS_SRC_COLOR: return MTLBlendFactorOneMinusSourceColor;
        case BlendFunction::DST_COLOR: return MTLBlendFactorDestinationColor;
        case BlendFunction::ONE_MINUS_DST_COLOR: return MTLBlendFactorOneMinusDestinationColor;
        case BlendFunction::SRC_ALPHA: return MTLBlendFactorSourceAlpha;
        case BlendFunction::ONE_MINUS_SRC_ALPHA: return MTLBlendFactorOneMinusSourceAlpha;
        case BlendFunction::DST_ALPHA: return MTLBlendFactorDestinationAlpha;
        case BlendFunction::ONE_MINUS_DST_ALPHA: return MTLBlendFactorOneMinusDestinationAlpha;
        case BlendFunction::SRC_ALPHA_SATURATE: return MTLBlendFactorSourceAlphaSaturated;
    }
}

static inline MTLCullMode getMetalCullMode(CullingMode cullMode) {
    switch (cullMode) {
        case CullingMode::NONE: return MTLCullModeNone;
        case CullingMode::FRONT: return MTLCullModeFront;
        case CullingMode::BACK: return MTLCullModeBack;
        case CullingMode::FRONT_AND_BACK:
            ASSERT_POSTCONDITION(false, "FRONT_AND_BACK culling is not supported in Metal.");
    }
}

static inline MTLPrimitiveType getMetalPrimitiveType(PrimitiveType type) {
    switch (type) {
        case PrimitiveType::POINTS: return MTLPrimitiveTypePoint;
        case PrimitiveType::LINES: return MTLPrimitiveTypeLine;
        case PrimitiveType::TRIANGLES: return MTLPrimitiveTypeTriangle;
        case PrimitiveType::NONE:
            ASSERT_POSTCONDITION(false, "NONE is not a valid primitive type.");
    }
}

} // namespace driver
} // namespace filament

#endif //TNT_FILAMENT_DRIVER_METALENUMS_H
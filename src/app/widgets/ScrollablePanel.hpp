// UnderStory
// An intuitive Pen & Paper experience
// Copyright (C) 2020 Guillaume Vara

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Any graphical resources available within the source code may
// use a different license and copyright : please refer to their metadata
// for further details. Graphical resources without explicit references to a
// different license and copyright still refer to this GPL.

#pragma once

#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Vector2.h>
#include <Magnum/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Timeline.h>

#include <utility>

#include "animation/BaseUIPlayerHelper.hpp"

#include "base/Constraints.hpp"
#include "base/Container.hpp"
#include "base/Toggleable.hpp"

// #include "Scroller.hpp"

#include "src/app/shaders/Shaders.hpp"

namespace UnderStory {

namespace Widget {

using namespace Magnum::Math::Literals;

class ScrollablePanel : public Animation::BaseUIPlayerHelper<Magnum::Float>, public Container<>, public Toggleable {
 public:
    enum StickTo {Left, Top, Right, Bottom};
    ScrollablePanel(StickTo sticking = StickTo::Left, float axisPrcSize = .6f) :
        BaseUIPlayerHelper(&_matrix, .2f, &_defaultAnimationCallback)
        // _scroller(&_matrix, _geometry) 
        {
        //
        _definePanelPosition(-X_PANEL_SIZE);
        _setup();
    }

    void mayDraw() {
        //
        if(!isToggled() && !isAnimationPlaying()) return;

        //
        // _scroller.mayDraw();

        //
        Shaders::flat
            ->setTransformationProjectionMatrix(_matrix)
            .setColor(0x000000AA_rgbaf)
            .draw(_mesh);
    }

    void onMouseScroll(const Magnum::Vector2& scrollOffset) {
        // TODO
        // _scroller.onMouseScroll(scrollOffset);
    }

 private:
    static constexpr float X_PANEL_SIZE = .8f;
    static constexpr float Y_PANEL_SIZE = 2.f;
    static constexpr Magnum::Vector2 BL_START {-1.f};
    static constexpr Magnum::Vector2 BL_END {BL_START.x() + X_PANEL_SIZE, BL_START.y() + Y_PANEL_SIZE};

    // Scroller _scroller;

    Magnum::Matrix3 _matrix;

    Magnum::GL::Mesh _mesh{Magnum::GL::MeshPrimitive::Triangles};

    static void _defaultAnimationCallback(Magnum::Float /*t*/, const float &prc, Animation::State<Magnum::Float>& state) {
        //
        state.current = Magnum::Math::lerp(
            state.from,
            state.to,
            Magnum::Animation::Easing::cubicOut(prc)
        );
    }

    void _onAnimationProgress() final {
        _definePanelPosition(currentAnim());
        _geometryUpdateRequested();
    }

    void _onToggled(bool isToggled) final {
        if(isToggled)
            _updateAnimationAndPlay(-X_PANEL_SIZE, 0.f);
        else
            _updateAnimationAndPlay(0.f, -X_PANEL_SIZE);
    }

    void _geometryUpdateRequested() final {
        _geometry = Magnum::Range2D {
            _matrix.transformPoint(BL_START),
            _matrix.transformPoint(BL_END)
        };
    }

    void _definePanelPosition(const Magnum::Float &xPos) {
        _replaceMainMatrix(
            Magnum::Matrix3::translation(
                Magnum::Vector2::xAxis(xPos)
            )
        );
    }

    void _setup() {
        // define indices
        Magnum::GL::Buffer bIndices, bVertexes;
        bIndices.setData({
            0, 1, 2,
            2, 3, 0
        });

        // define vertices
        struct Vertex {
            Magnum::Vector2 position;
        };
        const Vertex vertexes[]{
            {BL_START},
            {{ BL_END.x(),   BL_START.y() }},
            {BL_END},
            {{ BL_START.x(),  BL_END.y() }}
        };

        // bind buffer
        bVertexes.setData(vertexes, Magnum::GL::BufferUsage::StaticDraw);

        // define panel mesh
        _mesh.setCount(bIndices.size())
                .setIndexBuffer (std::move(bIndices),  0, Magnum::MeshIndexType::UnsignedInt)
                .addVertexBuffer(std::move(bVertexes), 0, Magnum::Shaders::Flat2D::Position{});
    }
};

}  // namespace Widget

}  // namespace UnderStory

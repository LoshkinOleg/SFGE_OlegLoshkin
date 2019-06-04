/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <engine/system.h>
#include <engine/engine.h>

#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <extensions/python_extensions.h>
#include <extensions/planet_system.h>

// Oleg Loshkin's systems.
#include <extensions/draw_quadtree_system.h>
#include <extensions/explosion_system.h>
#include <extensions/highlight_on_aabb_overlap_system.h>
#include <extensions/move_body_system.h>
#include <extensions/reset_scene_system.h>
#include <extensions/stay_on_screen_cpp_system.h>
#include <extensions/test_different_bodytypes_vs_forces_system.h>
#include <extensions/test_p2Vec2_system.h>

#include <tools/tools_pch.h>

namespace sfge::ext
{

static std::vector<std::function<void(py::module&)>> m_OtherPythonExtensions;

void ExtendPython(py::module& m)
{
	py::class_<PlanetSystem, System> planetSystem(m, "PlanetSystem");
	planetSystem
		.def(py::init<Engine&>());
	py::class_<DrawQuadTreeSystem, System> drawQuadTreeSystem(m, "DrawQuadTreeSystem");
	drawQuadTreeSystem
		.def(py::init<Engine&>());
	py::class_<ExplosionSystem, System> explosionSystem(m, "ExplosionSystem");
	explosionSystem
		.def(py::init<Engine&>());
	py::class_<HighlightOnAabbOverlapSystem, System> highlightOnAabbOverlapSystem(m, "HighlightOnAabbOverlapSystem");
	highlightOnAabbOverlapSystem
		.def(py::init<Engine&>());
	py::class_<MoveBodySystem, System> moveBodySystem(m, "MoveBodySystem");
	moveBodySystem
		.def(py::init<Engine&>());
	py::class_<ResetSceneSystem, System> resetSceneSystem(m, "ResetSceneSystem");
	resetSceneSystem
		.def(py::init<Engine&>());
	py::class_<StayOnScreenCppSystem, System> stayOnScreenCppSystem(m, "StayOnScreenCppSystem");
	stayOnScreenCppSystem
		.def(py::init<Engine&>());
	py::class_<TestDifferentBodytypesVsForcesSystem, System> testDifferentBodytypesVsForcesSystem(m, "TestDifferentBodytypesVsForcesSystem");
	testDifferentBodytypesVsForcesSystem
		.def(py::init<Engine&>());
	py::class_<TestP2Vec2System, System> testP2Vec2System(m, "TestP2Vec2System");
	testP2Vec2System
		.def(py::init<Engine&>());
	
	tools::ExtendPythonTools(m);
}

}

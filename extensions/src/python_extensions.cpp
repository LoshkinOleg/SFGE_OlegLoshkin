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
#include <extensions/test_01_system.h>
#include <extensions/test_02_system.h>
#include <extensions/test_03_system.h>
#include <extensions/test_04_system.h>
#include <extensions/test_05_system.h>
#include <extensions/test_06_system.h>
#include <extensions/test_07_system.h>
#include <extensions/test_08_system.h>
#include <extensions/test_09_system.h>
#include <extensions/test_10_system.h>

#include <tools/tools_pch.h>

namespace sfge::ext
{

static std::vector<std::function<void(py::module&)>> m_OtherPythonExtensions;

void ExtendPython(py::module& m)
{
	py::class_<PlanetSystem, System> planetSystem(m, "PlanetSystem");
	planetSystem
		.def(py::init<Engine&>());
	py::class_<Test_01_System, System> test_01_system(m, "Test_01_System");
	test_01_system
		.def(py::init<Engine&>());
	py::class_<Test_02_System, System> test_02_system(m, "Test_02_System");
	test_02_system
		.def(py::init<Engine&>());
	py::class_<Test_03_System, System> test_03_system(m, "Test_03_System");
	test_03_system
		.def(py::init<Engine&>());
	py::class_<Test_04_System, System> test_04_system(m, "Test_04_System");
	test_04_system
		.def(py::init<Engine&>());
	py::class_<Test_05_System, System> test_05_system(m, "Test_05_System");
	test_05_system
		.def(py::init<Engine&>());
	py::class_<Test_06_System, System> test_06_system(m, "Test_06_System");
	test_06_system
		.def(py::init<Engine&>());
	py::class_<Test_07_System, System> test_07_system(m, "Test_07_System");
	test_07_system
		.def(py::init<Engine&>());
	py::class_<Test_08_System, System> test_08_system(m, "Test_08_System");
	test_08_system
		.def(py::init<Engine&>());
	py::class_<Test_09_System, System> test_09_system(m, "Test_09_System");
	test_09_system
		.def(py::init<Engine&>());
	py::class_<Test_10_System, System> test_10_system(m, "Test_10_System");
	test_10_system
		.def(py::init<Engine&>());
	
	tools::ExtendPythonTools(m);
}

}

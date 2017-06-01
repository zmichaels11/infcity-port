#pragma once

#include <cstddef>

#include <gloop.hpp>

namespace infcity {
	namespace paths {
		int binomial(int n, int k) noexcept;

		gloop::vec3 bezier(float t, std::size_t pCount, const gloop::vec3 * points) noexcept;

		gloop::vec3 bspline(float t, std::size_t pCount, const gloop::vec3 * points) noexcept;
	}
}

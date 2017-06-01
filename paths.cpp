#include "paths.hpp"

#include <cmath>
#include <cstddef>

#include <array>
#include <iostream>

#include <gloop.hpp>

namespace infcity {
	namespace paths {
		namespace {
			static constexpr std::array<int, 1> _p0 = {1};
			static constexpr std::array<int, 2> _p1 = {1, 1};
			static constexpr std::array<int, 3> _p2 = {1, 2, 1};
			static constexpr std::array<int, 4> _p3 = {1, 3, 3, 1};
			static constexpr std::array<int, 5> _p4 = {1, 4, 6, 4, 1};
			static constexpr std::array<int, 6> _p5 = {1, 5, 10, 10, 5, 1};
			static constexpr std::array<int, 7> _p6 = {1, 6, 15, 20, 15, 6, 1};
			static constexpr std::array<int, 8> _p7 = {1, 7, 21, 35, 35, 21, 7, 1};
			static constexpr std::array<int, 9> _p8 = {1, 8, 28, 56, 70, 56, 28, 8, 1};
			static constexpr std::array<int, 10> _p9 = {1, 9, 36, 84, 126, 126, 84, 36, 9, 1};
		}

		int binomial(int n, int k) noexcept {
			switch (n) {
				default:
					std::cerr << "Unsupported binomial coefficients: "
						<< n
						<< ", " 
						<< k 
						<< std::endl;

					__builtin_trap();
					break;
				case 0:
					return _p0[k];
				case 1:
					return _p1[k];
				case 2:
					return _p2[k];
				case 3:
					return _p3[k];
				case 4:
					return _p4[k];
				case 5:
					return _p5[k];
				case 6:
					return _p6[k];
				case 7:
					return _p7[k];
				case 8:
					return _p8[k];
				case 9:
					return _p9[k];				
			}
		}

		gloop::vec3 bezier(float t, std::size_t nPoints, const gloop::vec3 * points) noexcept {
			gloop::vec3 value = {0.0F, 0.0F, 0.0F};

			for (std::size_t i = 0; i < nPoints; i++) {
				const auto frac = std::pow(t, i) * std::pow(1.0F - t, nPoints - 1 - i);
				const auto scalar = frac * binomial(nPoints - 1, i);
				const auto scaledPoint = gloop::vectors::scale(points[i], scalar);

				value = gloop::vectors::add(value, scaledPoint);
			}

			return value;
		}

		gloop::vec3 bspline(float _t, std::size_t nPoints, const gloop::vec3 * points) noexcept {
			_t *= (nPoints - 2);
			auto i = static_cast<int> (_t);

			if (i + 2 >= nPoints) {
				i = nPoints - 2;
			}

			const auto t = _t - i;
			const auto a = gloop::vectors::scale(gloop::vectors::add(points[i], points[i + 1]), 0.5F);
			const auto b = points[i + 1];
			const auto c = gloop::vectors::scale(gloop::vectors::add(points[i + 1], points[i + 2]), 0.5F);

			const auto tc = gloop::vectors::scale(c, t * t);
			const auto tb = gloop::vectors::scale(b, 2.0F * t * (1.0F - t));
			const auto ta = gloop::vectors::scale(a, (1.0F - t) * (1.0F - t));

			return gloop::vectors::add(tc, gloop::vectors::add(tb, ta));
		}
	}
}

#ifndef HD_STRUCTS_H_INCLUDED
#define HD_STRUCTS_H_INCLUDED

#include <array>

namespace Astro {

	namespace HumanDesign {

		extern std::array<int, 64> hd__gate_order;
		extern std::array<std::array<body, 6>, 64> exaltations;
		extern std::array<std::array<body, 6>, 64> detriments;
		extern std::array<std::array<int, 2>, 36> channels;		
	}
}

#endif // HD_STRUCTS_H_INCLUDED
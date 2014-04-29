#ifndef HUMANDESIGN_H_INCLUDED
#define HUMANDESIGN_H_INCLUDED

#include <string>
#include <forward_list>
#include "ephemeris.h"
#include "ecliptic.h"
#include "hd_structs.h"

namespace Astro {

	namespace HumanDesign {

		using namespace std;

		enum class side : int { personality, design };

		struct Activation {

			body b;
			bool detrimented, exalted;
			int gate, line;
			int pos;

			Activation() : detrimented{ false }, exalted{ false } {}
		};

		class Rave {

		public:

			Rave(const DateTime& dt);			
			Rave(double jd);
			Rave(const Rave&) = delete;

			inline int pos(side s, body b) const {

				return activations[static_cast<int>(s)][static_cast<int>(b)].pos;
			}

			inline bool isDetrimented(side s, body b) const {

				return activations[static_cast<int>(s)][static_cast<int>(b)].detrimented;
			}

			inline bool isExalted(side s, body b) const {

				return activations[static_cast<int>(s)][static_cast<int>(b)].exalted;
			}

		private:

			std::array<std::array<Activation, bodies_N>, 2> activations;

			void applyDetriments();
		};

		void activ(int pos, int *gate, int *line);

		extern double design_date_angle;
		
		double design_date(double jd);
		double design_date(const Date& d, const Time& t);
		double design_date(const DateTime& dt);
		
		void add_connected_gates(int gate, std::forward_list<int>& gates);
	}
} // namespace 

#endif // HUMANDESIGN_H_INCLUDED


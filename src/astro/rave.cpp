#include <forward_list>
#include <algorithm>
#include "ephemeris.h"
#include "hd_structs.h"
#include "humandesign.h"

namespace Astro {

	namespace HumanDesign {

		using namespace Ephemeris;

		Rave::Rave(double jd)
		{		
			Ecliptic::Divider<384> div(223.25);
						
			double d_date = design_date(jd);
			
			for(int i = 0; i < bodies_N; ++i) {

				body b = static_cast<body>(i);

				double personality = ephemeris->pos(b, jd);
				double design = ephemeris->pos(b, d_date);

				Activation p, d;
				p.b = b;
				d.b = b;
				p.pos = div.pos(personality);
				d.pos = div.pos(design);
				activ(p.pos, &p.gate, &p.line);
				activ(d.pos, &d.gate, &d.line);

				activations[0][i] = p;
				activations[1][i] = d;
			}

			applyDetriments();
		}

		Rave::Rave(const DateTime& dt)
		:
			Rave(Utilities::to_julian_day(dt.date(), dt.time()))
		{			
		}

		void Rave::applyDetriments()
		{
			forward_list<Activation*> to_process;

			for(int i = 0; i < int(activations.size()); ++i)
				for(int j = 0; j < bodies_N; ++j)
					to_process.push_front(&activations[i][j]);

			for(auto a : to_process) {

				forward_list<int> gates;
				gates.push_front(a->gate);
				add_connected_gates(a->gate, gates);

				body e = exaltations[a->gate - 1][a->line - 1];
				body d = detriments[a->gate - 1][a->line - 1];

				for(auto b : to_process) {

					if(e == b->b) {

						if(find(gates.begin(), gates.end(), b->gate) != gates.end())
							a->exalted = true;
					}

					if(d == b->b) {

						if(find(gates.begin(), gates.end(), b->gate) != gates.end())
							a->detrimented = true;
					}
				}
			}
		}
	} // namespace
} // namespace


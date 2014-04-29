#include <string>
#include <array>
#include <vector>

#include "humandesign.h"
#include "astro.h"
#include "hd_structs.h"

namespace Astro {

	namespace HumanDesign {

		using namespace std;
		using namespace Ephemeris;

		void activ(int pos, int *gate, int *line)
		{
			*gate = hd__gate_order[pos / 6];
			*line = pos % 6 + 1;	
		}			

		double get_val_delta(double current_date, double target_pos)
		{
			double current_pos{ ephemeris->pos(body::sun, current_date) };
			double delta;

			if(current_pos > 350. && target_pos < 10.) {

				delta = current_pos - 360. - target_pos;				
			}
			else if(current_pos < 10. && target_pos > 350.) {

				delta = 360. - target_pos + current_pos;				
			}
			else {

				delta = current_pos - target_pos;				
			}

			return delta;
		}
		
		const double prec = 1e-7;

		double find_design_date(double current_date, double target_pos)
		{
			double current_delta { get_val_delta(current_date, target_pos)	}, step{ 1. };

			if(fabs(current_delta) < prec) return current_date;

			while(1) {

				while(current_delta < 0) {

					current_date += step;
					current_delta = get_val_delta(current_date, target_pos);
					
					if(fabs(current_delta) < prec) return current_date;
				}

				while(current_delta > 0) {

					current_date -= step;
					current_delta = get_val_delta(current_date, target_pos);

					if(fabs(current_delta) < prec) return current_date;
				}

				step /= 5;
			}

			return current_date;
		}

		double design_date_angle = -88.;

		double design_date(double jd)
		{
			double target = ephemeris->pos(body::sun, jd) + design_date_angle; // -88 degrees
			if(target < 0) target += 360.;
			else if(target > 360.) target -= 360.;

			return find_design_date(jd + design_date_angle, target); // -88 days
		}

		double design_date(const Date& d, const Time& t)
		{
			return design_date(Utilities::to_julian_day(d, t));
		}

		double design_date(const DateTime& dt)
		{
			return design_date(dt.date(), dt.time());
		}

		void add_connected_gates(int gate, std::forward_list<int>& gates)
		{
			for(size_t i = 0; i < channels.size(); ++i) {

				if(channels[i][0] == gate)
					gates.push_front(channels[i][1]);

				if(channels[i][1] == gate)
					gates.push_front(channels[i][0]);
			}
		}
	} // namespace
} // namespace
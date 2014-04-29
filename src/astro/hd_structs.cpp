#include "datetime.h"
#include "hd_structs.h"

namespace Astro {

	namespace HumanDesign {
		
		using namespace std;

		/*
		 According to 'The Complete Rave I'Ching', Ra Uru Hu, 2001
		*/

		array<int, 64> hd__gate_order{ {

			1, 43, 14, 34, 9,  5,  26, 11, 10, 58, 38, 54, 61, 60, 41, 19, 13, 49, 30, 55, 37, 63, 22, 36, 25, 17, 21, 51, 42,  3, 27, 24,
			2, 23, 8,  20, 16, 35, 45, 12, 15, 52, 39, 53, 62, 56, 31, 33, 7,  4,  29, 59, 40, 64, 47, 6,  46, 18, 48, 57, 32, 50, 28, 44
		} };		

		array<array<body, 6>, 64> exaltations = { {

			// 1
			{ body::moon, body::venus, body::mars, body::earth, body::mars, body::earth },
			{ body::venus, body::saturn, body::jupiter, body::venus, body::mercury, body::mercury },
			{ body::earth, body::mars, body::venus, body::neptune, body::mars, body::sun },
			{ body::moon, body::moon, body::venus, body::sun, body::jupiter, body::mercury },

			// 5
			{ body::mars, body::venus, body::neptune, body::uranus, body::venus, body::neptune },
			{ body::pluto, body::venus, body::neptune, body::sun, body::venus, body::mercury },
			{ body::venus, body::neptune, body::moon, body::sun, body::venus, body::mercury },
			{ body::neptune, body::sun, body::moon, body::jupiter, body::jupiter, body::venus },			
		
			// 9
			{ body::pluto, body::pluto, body::earth, body::moon, body::jupiter, body::moon },
			{ body::sun, body::mercury, body::earth, body::uranus, body::jupiter, body::pluto },
			{ body::moon, body::neptune, body::pluto, body::moon, body::moon, body::neptune },
			{ body::venus, body::saturn, body::neptune, body::earth, body::sun, body::sun },

			// 13
			{ body::venus, body::moon, body::earth, body::pluto, body::neptune, body::mars },
			{ body::jupiter, body::jupiter, body::earth, body::moon, body::sun, body::sun },
			{ body::venus, body::sun, body::earth, body::jupiter, body::jupiter, body::pluto },
			{ body::earth, body::sun, body::moon, body::jupiter, body::pluto, body::neptune },

			// 17
			{ body::mars, body::sun, body::pluto, body::pluto, body::uranus, body::moon },
			{ body::earth, body::pluto, body::neptune, body::earth, body::saturn, body::mars },
			{ body::sun, body::jupiter, body::venus, body::mars, body::earth, body::jupiter },
			{ body::venus, body::venus, body::sun, body::jupiter, body::saturn, body::venus },

			// 21
			{ body::mars, body::mars, body::neptune, body::jupiter, body::jupiter, body::pluto },
			{ body::moon, body::sun, body::saturn, body::neptune, body::jupiter, body::sun },
			{ body::jupiter, body::jupiter, body::sun, body::sun, body::jupiter, body::mars },
			{ body::sun, body::moon, body::venus, body::saturn, body::moon, body::jupiter },

			// 25
			{ body::neptune, body::mercury, body::mars, body::venus, body::venus, body::earth },
			{ body::neptune, body::sun, body::sun, body::pluto, body::mars, body::sun },
			{ body::sun, body::moon, body::pluto, body::jupiter, body::jupiter, body::moon },
			{ body::mars, body::sun, body::saturn, body::jupiter, body::pluto, body::pluto },

			// 29
			{ body::mars, body::sun, body::mars, body::saturn, body::sun, body::mars },
			{ body::sun, body::sun, body::pluto, body::pluto, body::jupiter, body::mars },
			{ body::sun, body::jupiter, body::sun, body::moon, body::pluto, body::sun },
			{ body::sun, body::venus, body::mercury, body::jupiter, body::moon, body::pluto },

			// 33
			{ body::sun, body::jupiter, body::jupiter, body::pluto, body::pluto, body::sun },
			{ body::saturn, body::mars, body::saturn, body::pluto, body::mars, body::earth },
			{ body::venus, body::venus, body::jupiter, body::moon, body::mercury, body::saturn },
			{ body::mars, body::neptune, body::pluto, body::pluto, body::pluto, body::jupiter },

			// 37
			{ body::venus, body::jupiter, body::jupiter, body::moon, body::venus, body::venus },
			{ body::neptune, body::pluto, body::sun, body::pluto, body::saturn, body::saturn },
			{ body::mars, body::moon, body::jupiter, body::moon, body::neptune, body::moon },
			{ body::sun, body::sun, body::pluto, body::uranus, body::uranus, body::sun },

			// 41
			{ body::neptune, body::saturn, body::saturn, body::earth, body::mars, body::saturn },
			{ body::sun, body::sun, body::mars, body::moon, body::sun, body::moon },
			{ body::pluto, body::pluto, body::pluto, body::mercury, body::moon, body::sun },
			{ body::pluto, body::jupiter, body::mars, body::pluto, body::uranus, body::pluto },

			// 45
			{ body::jupiter, body::uranus, body::neptune, body::jupiter, body::uranus, body::uranus },
			{ body::neptune, body::sun, body::moon, body::earth, body::moon, body::saturn },
			{ body::saturn, body::saturn, body::jupiter, body::saturn, body::venus, body::null_body },
			{ body::moon, body::pluto, body::moon, body::sun, body::mars, body::venus },

			// 49
			{ body::jupiter, body::earth, body::neptune, body::jupiter, body::moon, body::neptune },
			{ body::mars, body::sun, body::moon, body::saturn, body::saturn, body::venus },
			{ body::pluto, body::mars, body::sun, body::uranus, body::sun, body::sun },
			{ body::earth, body::venus, body::saturn, body::saturn, body::earth, body::venus },

			// 53
			{ body::neptune, body::moon, body::moon, body::moon, body::neptune, body::moon },
			{ body::pluto, body::saturn, body::pluto, body::null_body, body::sun, body::saturn },
			{ body::jupiter, body::venus, body::saturn, body::jupiter, body::uranus, body::saturn },
			{ body::moon, body::uranus, body::sun, body::moon, body::uranus, body::sun },

			// 57
			{ body::venus, body::venus, body::mercury, body::venus, body::pluto, body::uranus },
			{ body::venus, body::null_body, body::uranus, body::pluto, body::moon, body::moon },
			{ body::sun, body::uranus, body::saturn, body::venus, body::sun, body::venus },
			{ body::venus, body::saturn, body::saturn, body::mercury, body::neptune, body::uranus },

			// 61
			{ body::neptune, body::moon, body::moon, body::saturn, body::saturn, body::pluto },
			{ body::neptune, body::saturn, body::uranus, body::venus, body::moon, body::saturn },
			{ body::sun, body::jupiter, body::jupiter, body::mercury, body::sun, body::jupiter },
			{ body::venus, body::venus, body::saturn, body::moon, body::venus, body::mercury }
		} };

		array<array<body, 6>, 64> detriments = { {

			// 1
			{ body::uranus, body::mars, body::earth, body::jupiter, body::uranus, body::pluto },
			{ body::mars, body::mars, body::uranus, body::mars, body::earth, body::saturn },
			{ body::mercury, body::uranus, body::pluto, body::mars, body::earth, body::pluto },
			{ body::earth, body::mars, body::pluto, body::saturn, body::pluto, body::mars },

			// 5
			{ body::earth, body::pluto, body::moon, body::sun, body::pluto, body::null_body },
			{ body::mercury, body::mars, body::pluto, body::pluto, body::moon, body::venus },
			{ body::mercury, body::mercury, body::mercury, body::uranus, body::neptune, body::uranus },
			{ body::mercury, body::earth, body::saturn, body::mercury, body::sun, body::pluto },

			// 9
			{ body::mars, body::jupiter, body::sun, body::mars, body::earth, body::pluto },
			{ body::moon, body::mars, body::moon, body::mercury, body::mars, body::saturn },
			{ body::mars, body::mars, body::venus, body::sun, body::mercury, body::jupiter },
			{ body::jupiter, body::mercury, body::mars, body::mercury, body::mars, body::earth },

			// 13
			{ body::moon, body::sun, body::venus, body::venus, body::jupiter, body::mercury },
			{ body::mercury, body::mars, body::neptune, body::mars, body::venus, body::earth },
			{ body::mars, body::earth, body::mercury, body::saturn, body::pluto, body::venus },
			{ body::mercury, body::mercury, body::mars, body::mars, body::moon, body::jupiter },

			// 17
			{ body::venus, body::moon, body::earth, body::jupiter, body::mars, body::jupiter },
			{ body::jupiter, body::moon, body::jupiter, body::mercury, body::uranus, body::moon },
			{ body::moon, body::mercury, body::moon, body::venus, body::jupiter, body::mars },
			{ body::moon, body::moon, body::earth, body::mercury, body::uranus, body::mercury },

			// 21
			{ body::moon, body::neptune, body::jupiter, body::earth, body::pluto, body::venus },
			{ body::mars, body::jupiter, body::mars, body::mars, body::mars, body::mars },
			{ body::mars, body::moon, body::pluto, body::earth, body::moon, body::jupiter },
			{ body::neptune, body::mars, body::jupiter, body::neptune, body::mars, body::pluto },

			// 25
			{ body::mercury, body::mars, body::pluto, body::null_body, body::jupiter, body::uranus },
			{ body::mars, body::pluto, body::saturn, body::saturn, body::venus, body::moon },
			{ body::earth, body::mars, body::mars, body::mars, body::saturn, body::pluto },
			{ body::venus, body::jupiter, body::jupiter, body::mercury, body::sun, body::neptune },

			// 29
			{ body::neptune, body::venus, body::jupiter, body::venus, body::earth, body::jupiter },
			{ body::jupiter, body::mars, body::jupiter, body::jupiter, body::pluto, body::moon },
			{ body::earth, body::mercury, body::jupiter, body::mars, body::moon, body::moon },
			{ body::mars, body::jupiter, body::jupiter, body::saturn, body::mars, body::neptune },

			// 33
			{ body::mars, body::neptune, body::mars, body::neptune, body::jupiter, body::jupiter },
			{ body::pluto, body::venus, body::mercury, body::mars, body::moon, body::jupiter },
			{ body::neptune, body::moon, body::sun, body::mars, body::jupiter, body::mars },
			{ body::jupiter, body::moon, body::jupiter, body::moon, body::mercury, body::saturn },

			// 37
			{ body::null_body, body::mercury, body::mars, body::saturn, body::mars, body::mercury },
			{ body::mars, body::moon, body::earth, body::mars, body::pluto, body::earth },
			{ body::mercury, body::jupiter, body::earth, body::sun, body::mars, body::mars },
			{ body::moon, body::moon, body::mars, body::mars, body::earth, body::earth },

			// 41
			{ body::mercury, body::mars, body::moon, body::venus, body::venus, body::pluto },
			{ body::venus, body::venus, body::moon, body::venus, body::venus, body::saturn },
			{ body::venus, body::moon, body::moon, body::jupiter, body::venus, body::mars },
			{ body::venus, body::mars, body::neptune, body::sun, body::mars, body::earth },

			// 45
			{ body::mars, body::mars, body::mars, body::mars, body::jupiter, body::jupiter },
			{ body::jupiter, body::mars, body::mars, body::pluto, body::neptune, body::neptune },
			{ body::neptune, body::mercury, body::mars, body::moon, body::null_body, body::sun },
			{ body::mars, body::venus, body::mercury, body::earth, body::moon, body::moon },

			// 49
			{ body::sun, body::pluto, body::pluto, body::mars, body::mars, body::saturn },
			{ body::venus, body::venus, body::mercury, body::mars, body::mars, body::moon },
			{ body::venus, body::mercury, body::jupiter, body::mercury, body::mars, body::pluto },
			{ body::mars, body::mars, body::venus, body::jupiter, body::pluto, body::neptune },

			// 53
			{ body::venus, body::mars, body::mars, body::venus, body::earth, body::pluto },
			{ body::venus, body::mars, body::venus, body::null_body, body::null_body, body::jupiter },
			{ body::venus, body::earth, body::mars, body::mars, body::sun, body::moon },
			{ body::mars, body::moon, body::venus, body::mercury, body::mars, body::pluto },

			// 57
			{ body::moon, body::moon, body::null_body, body::mars, body::moon, body::mars },
			{ body::moon, body::uranus, body::mars, body::neptune, body::sun, body::mercury },
			{ body::mercury, body::pluto, body::mars, body::mercury, body::uranus, body::mercury },
			{ body::mercury, body::earth, body::mars, body::venus, body::jupiter, body::mercury },

			// 61
			{ body::venus, body::mars, body::mars, body::jupiter, body::mars, body::mars },
			{ body::mars, body::mercury, body::venus, body::pluto, body::neptune, body::mercury },
			{ body::mars, body::uranus, body::saturn, body::mars, body::mars, body::pluto },
			{ body::mars, body::moon, body::moon, body::mars, body::jupiter, body::venus }
		} };
		
		array<array<int, 2>, 36> channels = { {
			{ 1, 8 },    // Inspiration - design of Creative Role Model
			{ 2, 14 },   // Beat - design of being a Keeper of Keys
			{ 3, 60 },   // Mutation - design of Energy which Fluctuates and Initiates, Pulse
			{ 4, 63 },   // Logic - design of Mental Ease mixed with Doubt
			{ 5, 15 },   // Rhythm - design of Being in the Flow
			{ 6, 59 },   // Mating - design of Focused on Reproduction
			{ 7, 31 },   // The Alpha - design of Leadership for 'good' or 'bad'
			{ 9, 52 },   // Concentration - design of Determination, Focused
			{ 10, 20 },  // Awekening - design of Commitment to Higher Principles
			{ 10, 34 },  // Exploration - design of Following one's Convitcions
			{ 10, 57 },  // Perfected Form - design of Survival
			{ 11, 56 },  // Curiosity - design of a Searcher
			{ 12, 22 },  // Openness - design of a Social Being
			{ 13, 33 },  // Prodigal - design of a Witness
			{ 16, 48 },  // Wavelength - design of a Talent
			{ 17, 62 },  // Acceptance - design of an Organizational Being
			{ 18, 58 },  // Judgement - design of Insatiability
			{ 19, 49 },  // Synthesis - design of a Sensitivity
			{ 20, 34 },  // Charisma - design where Thoughts must become Deeds
			{ 20, 57 },  // Brainwave - design of Penetrating Awareness
			{ 21, 45 },  // Money Line - design of a Materialist
			{ 23, 43 },  // Structuring - design of Individuality
			{ 24, 61 },  // Awareness - design of a Thinker
			{ 25, 51 },  // Initiation - design of Needing to be First
			{ 26, 44 },  // Surrender - design of a Transmitter
			{ 27, 50 },  // Preservation - design of a Custodianship
			{ 28, 38 },  // Struggle - design of Stubbornness
			{ 29, 46 },  // Discovery - design of Succeeding where others Fail
			{ 30, 41 },  // Recognition - design of Focused Energy
			{ 32, 54 },  // Transformation - design of Being Driven
			{ 34, 57 },  // Power - design of an Archetype
			{ 35, 36 },  // Transitoriness - design of 'Jack of all Trades'
			{ 37, 40 },  // Community - design of being a Part seeking a Whole
			{ 39, 55 },  // Emoting - design of Moodiness
			{ 42, 53 },  // Maturiation - design of Balanced Development, Cyclic
			{ 47, 64 },  // Abstraction - design of Mental Activity mixed with Clarity
		} };
	} // namespace
} // namespace
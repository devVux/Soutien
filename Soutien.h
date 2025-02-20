#pragma once
#include <iostream>
#include <tuple>

namespace Soutien {

	template<class Func, class... Requirements>
	struct GuardedFunction {

		public:

			GuardedFunction(Func func, const char* name, Requirements... reqs)
				: mFunction(func), mName(name), mRequirements(reqs...) {}

			void operator()() {
				bool allMet = true;
				std::apply([&](const auto&... req) {
					((allMet &= req.satisfied() || 
						(std::cout << "Dependency `" << req.name() 
						<< "` not met. Blocking `" << mName << "`\n", false)), ...);
				}, mRequirements);

				if (allMet) {
					mFunction();
					mSatisfied = true;
				}
			}

			bool satisfied() const { return mSatisfied; }
			const char* name() const { return mName; }


		private:

			Func mFunction;
			const char* mName;
			std::tuple<Requirements...> mRequirements;
			bool mSatisfied { false };

	};

	template<class Func, class... Dependencies>
	auto createGuardedFunction(Func f, const char* name, Dependencies... deps) {
		return GuardedFunction<Func, Dependencies...>(f, name, deps...);
	}

}

#define GUARDED_FUNCTION(func, ...) \
    Soutien::createGuardedFunction(func, #func, ##__VA_ARGS__)


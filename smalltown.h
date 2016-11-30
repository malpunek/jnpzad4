#ifndef smalltowner
#define smalltowner
#include <tuple>
#include <string>

template<typename M, typename U, U t0, U t1, typename ... C>
class SmallTown{
	private:
		typedef std::tuple<C...> C_type;
		typedef M M_type;
		C_type citizens;
		M_type monster;
		U current_time = t0, max_time = t1;
	public:
		SmallTown(M m, C... c);
		void tick(U timeStep);
		std::tuple<std::string, typename M::valueType, size_t> getStatus();
};
#endif

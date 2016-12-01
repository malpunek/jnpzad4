#include <cstdio>
#include <tuple>
#include "citizen.h"
#include "monster.h"
using namespace std;

/*
Klasa SmallTown<typename M, typename U, U t0, U t1, typename... C>, gdzie:
M – typ potwora nawiedzającego miasto,
U – typ przechowujący czas,
t0 – czas startowy,
t1 – czas końcowy, po którego przekroczeniu następuje wyzerowanie licznika,
C... – typy mieszkańców.
Należy sprawdzać poprawność parametrów t0 i t1 w czasie kompilacji.
*/
		constexpr const char CITIZENS_WON[] = "CITIZENS WON";
		constexpr const char MONSTER_WON[] = "MONSTER WON";
		constexpr const char DRAW[] = "DRAW";

template<typename M, typename U, U t0, U t1, typename ... C>
class SmallTown{
	private:
		bool attack_time;
		typedef tuple<C...> C_type;
		typedef M M_type;
		C_type citizens;
		M_type monster;
		U current_time = t0, max_time = t1;
		
		size_t countAliveCitizens(){
			size_t wynik = 1;
	/*		for(size_t i = 0; i < sizeof...(C); ++i)
				if (get<i>(citizens).isAlive())
					wynik++;*/
			return wynik;
		}

		bool isCityDead(){
			return countAliveCitizens() == 0;
		}

		template<typename T>
		void attacker(T firster){
			attack(monster, firster);
		}
		
		template<typename T, typename ... Ts>
		void attacker(T firster, Ts ... lasts){
			attack(monster, firster);
			attacker(lasts...);
		}

			
		template<std::size_t... Is>
		void attackEveryone(std::index_sequence<Is...>){
			attacker(get<Is>(citizens)...);
			}
	public:
		
		SmallTown(M m, C... c) : citizens(c...), monster(m), attack_time(false){};
		


		void tick(U timeStep){
			if (!monster.isAlive())
				printf("%s\n", isCityDead() ? DRAW:CITIZENS_WON);
			else if (isCityDead())
			   printf("%s\n", MONSTER_WON);	   
			else {
				for (int i = 0; i < 80; i++)
					if (current_time == U(fib<i>::val)) //@TODO CAST, MAX_FIB as const
						attack_time = true;
				if (attack_time)
					attackEveryone(std::index_sequence_for<C...>{});
		//			for(size_t i = 0; i < sizeof...(C); ++i)
		//				attack(monster, get<i>(citizens));
				}
			while (current_time + timeStep > max_time){
				timeStep -= max_time - current_time;
				current_time = max_time - max_time;
				}
			current_time += timeStep;
		}

		tuple<string, typename M::valueType, size_t> getStatus(){
			return make_tuple(monster.getName(), monster.getHealth(), countAliveCitizens());
		}

};


/*
SmallTown operuje zgodnie z wewnętrznym zegarem. Czas liczony jest w godzinach,
od godziny 0 do godziny t1 i potem znów od godziny 0, i tak cyklicznie. Pierwsze
odliczanie zaczyna się od godziny t0. Potwór atakuje tylko o godzinach równych
kolejnym liczbom z ciągu Fibonacciego. Obliczenie wszystkich potrzebnych liczb
z tego ciągu i ich zapamiętanie w jakiejś kolekcji musi odbyć się w czasie
kompilacji.

Śmierć mieszkańca bądź potwora następuje w momencie, gdy jego liczba punktów
życia osiągnie zero. Wywołanie tick() na miasteczku z martwym potworem i co
najmniej jednym żywym mieszkańcem powoduje wypisanie na standardowe wyjście
komunikatu "CITIZENS WON". Wywołanie tick() na miasteczku z martwymi
mieszkańcami i żywym potworem powoduje wypisanie na standardowym wyjściu napisu
"MONSTER WON". Jeśli zarówno mieszańcy, jak i potwór są martwi, to tick()
wypisuje na standardowe wyjście "DRAW".
*/

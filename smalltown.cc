#include<cstdio>
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

template<typename M, typename U, U t0, U t1, typename ... C>
class SmallTown{
	private:
		typedef tuple<C...> C_type;
		typedef M M_type;
		C_type citizens;
		M_type monster;
		U current_time = t0, max_time = t1;
	public:
		/*	Klasa SmallTown przyjmuje w konstruktorze obiekt reprezentujący bestię oraz
		kolejno obiekty mieszkańców.	*/
		SmallTown(M m, C... c) : citizens(c...), monster(m){};
		/*	void tick(U timeStep) – na początku sprawdza aktualny czas; jeśli jest to
		czas ataku, to następuje atak na wszystkich mieszkańców; na koniec czas
		w miasteczku przesuwa się o timeStep.	*/
		
		void tick(U timeStep){
		
		}

		/*	tuple<string, T, size_t> getStatus() – zwraca nazwę typu potwora, liczbę jego
		punktów życia (typu T) oraz liczbę pozostałych przy życiu mieszkańców;	*/
		
		tuple<string, typename M::valueType, size_t> getStatus(){
			return make_tuple(monster.getName(), monster.getHealth(), tuple_size<C_type>::value);
			//@TODO
			//czy getName nie powinien być static?
			//size się nie zgadza
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

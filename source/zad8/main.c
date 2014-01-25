/**
 * Zadanie 8.
 * Napisz program, który zbiera komunikaty od wielu programów i
 * wyświetla je na ekranie. Do komunikacji użyj potoku nazwanego.
 * Wskazówka: Utwórz program rdfifo, którego zadaniem jest utworzenie
 * kolejki FIFO i czytanie z niej danych. Utwórz program wrfifo, który
 * otwiera kolejkę FIFO tylko do zapisu i wpisuje do niej dane (np. swoj
 * pid i czas). W jaki sposób przekażesz wspólną nazwę kolejki FIFO do
 * tych programów? W jaki sposób zapewnić działanie programu
 * zbierającego komunikaty również wtedy, kiedy nie ma programu
 * piszącego do łącza? Jak zapewnić to, że komunikaty pochodzące od
 * różnych programów wyświetlane są w całości, tzn. nie są rozdzielane
 * komunikatami od innych programów?
 */
#include <stdio.h>

int main(int argc, char * argv[]) {
    return 0;
}

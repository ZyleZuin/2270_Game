
EXPENDABLES = cards
# if all is the first line, make builds every file in the project

all:
	@make $(EXPENDABLES)
cards: cards.cpp
	g++ -Wall -gstabs cards.cpp -o cards
clean:
	rm $(EXPENDABLES)

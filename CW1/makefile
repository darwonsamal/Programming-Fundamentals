sentences:
	     cl /c functions.c
	     lib /OUT:spell.lib functions.obj
	     cl /c spell.c
	     link spell.obj spell.lib

       spell -i sentences_test.txt -o output.txt

sentencesCase:
			cl /c functions.c
 			lib /OUT:spell.lib functions.obj
 			cl /c spell.c
 			link spell.obj spell.lib

	    spell -i sentences_test.txt -o output.txt -c

singleWord:
			cl /c functions.c
			lib /OUT:spell.lib functions.obj
			cl /c spell.c
			link spell.obj spell.lib

	    spell -i single_words_test.txt -o output.txt

singleWordCase:
			cl /c functions.c
			lib /OUT:spell.lib functions.obj
			cl /c spell.c
			link spell.obj spell.lib

	    spell -i single_words_test.txt -o output.txt -c

clean:
	    del *.exe
			del *.obj

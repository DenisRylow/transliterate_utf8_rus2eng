/*
 * main_transliterate.cpp
 *
 *  Created on: 17 сент. 2016 г.
 *      Author: Dexiz
 */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//#include <locale>
//#include <boost/locale.hpp>
#include <cctype>
#include <cstring>


int FindCharacterIndexInArray(char16_t character, char16_t *array, int arraySize)
{
	int i = 0;
	bool elementFound = false;

	while(i < arraySize && !elementFound)
	{
		elementFound = *(array + i) == character;
		++i;
	};
	//for( std::size_t i = 0; i < arraySize, ++i)
		//array + i;

	return i - 1;
}

int main()
{
	//This program transliterates Russian utf8 symbols into Latin alphabet according to ISO 9 (ГОСТ 7.79).

	char16_t rusAlphabet[66] {};

	rusAlphabet[0] =  0xD001; // Big russian YO (Ё) - 0xD001.
	int i;

	char16_t bigA =  0xD090 - 1;
	// Inserting capitals: from A(А) to YA(Я) but without YO(Ё);
	for( i = 1; i < 33; ++i )
		rusAlphabet[i] = bigA + i;

	char16_t smallA =  0xD0B0 - 33;
	// Inserting minuscules: from a(a) to p(п) but without yo(ё);
	for( ; i < 49; ++i ) // i = 33
		rusAlphabet[i] = smallA + i;

	char16_t smallR =  0xD180 - 49;
	// Inserting minuscules: from r(р) to ya(я) but without yo(ё);
	for( ; i < 65; ++i ) // i = 50
		rusAlphabet[i] = smallR + i;

	rusAlphabet[65] =  0xD191; // Small russian yo (ё) - 0xD191.


	char rusToEngTransliterationAlphabet[66][4] {}; // char is enough, even though symbols are utf8.

	rusToEngTransliterationAlphabet[0][0] = *u8"Y";
	rusToEngTransliterationAlphabet[0][1] = *u8"O";

	rusToEngTransliterationAlphabet[65][0] = *u8"y";
	rusToEngTransliterationAlphabet[65][1] = *u8"o";

	rusToEngTransliterationAlphabet[1][0] = *u8"A";
	rusToEngTransliterationAlphabet[2][0] = *u8"B";
	rusToEngTransliterationAlphabet[3][0] = *u8"V";
	rusToEngTransliterationAlphabet[4][0] = *u8"G";
	rusToEngTransliterationAlphabet[5][0] = *u8"D";
	rusToEngTransliterationAlphabet[6][0] = *u8"E";
	rusToEngTransliterationAlphabet[7][0] = *u8"Z";
	rusToEngTransliterationAlphabet[7][1] = *u8"H";
	rusToEngTransliterationAlphabet[8][0] = *u8"Z";
	rusToEngTransliterationAlphabet[9][0] = *u8"I";
	rusToEngTransliterationAlphabet[10][0] = *u8"J";
	rusToEngTransliterationAlphabet[11][0] = *u8"K";
	rusToEngTransliterationAlphabet[12][0] = *u8"L";
	rusToEngTransliterationAlphabet[13][0] = *u8"M";
	rusToEngTransliterationAlphabet[14][0] = *u8"N";
	rusToEngTransliterationAlphabet[15][0] = *u8"O";
	rusToEngTransliterationAlphabet[16][0] = *u8"P";
	rusToEngTransliterationAlphabet[17][0] = *u8"R";
	rusToEngTransliterationAlphabet[18][0] = *u8"S";
	rusToEngTransliterationAlphabet[19][0] = *u8"T";
	rusToEngTransliterationAlphabet[20][0] = *u8"U";
	rusToEngTransliterationAlphabet[21][0] = *u8"F";
	rusToEngTransliterationAlphabet[22][0] = *u8"X";
	rusToEngTransliterationAlphabet[23][0] = *u8"C";
	rusToEngTransliterationAlphabet[23][1] = *u8"Z";

	rusToEngTransliterationAlphabet[24][0] = *u8"C";
	rusToEngTransliterationAlphabet[24][1] = *u8"H";

	rusToEngTransliterationAlphabet[25][0] = *u8"S";
	rusToEngTransliterationAlphabet[25][1] = *u8"H";

	rusToEngTransliterationAlphabet[26][0] = *u8"S";
	rusToEngTransliterationAlphabet[26][1] = *u8"H";
	rusToEngTransliterationAlphabet[26][2] = *u8"H";

	rusToEngTransliterationAlphabet[27][0] = *u8"'";
	rusToEngTransliterationAlphabet[27][1] = *u8"'";

	rusToEngTransliterationAlphabet[28][0] = *u8"Y";
	rusToEngTransliterationAlphabet[28][1] = *u8"'";

	rusToEngTransliterationAlphabet[29][0] = *u8"'";

	rusToEngTransliterationAlphabet[30][0] = *u8"E";
	rusToEngTransliterationAlphabet[30][1] = *u8"'";

	rusToEngTransliterationAlphabet[31][0] = *u8"Y";
	rusToEngTransliterationAlphabet[31][1] = *u8"U";

	rusToEngTransliterationAlphabet[32][0] = *u8"Y";
	rusToEngTransliterationAlphabet[32][1] = *u8"A";

	int minisculeLetterStart= 32;
	for( i = 1; i < 33; ++i)
		for( int j = 0; j < 4; ++j)
			rusToEngTransliterationAlphabet[i + minisculeLetterStart][j] = std::tolower(rusToEngTransliterationAlphabet[i][j]);


	//std::locale loc = std::get ;
	//auto tempCharacter = boost::locale::to_lower( rusToEngTransliterationAlphabet[0][0], loc ) ;
	//std::locale::
	//std::iostream::basic_istream inputFile("test.bib");
	//std::fstream::basic_fstream inputFile("test.bib");
	//std::fstream::basic_istream inputFile("test.bib");

	//std::iostream::basic_ostream outputFile("test2.bib");
	//std::fstream::basic_ostream outputFile("test2.bib");

	//std::ifstream inputFile("test.bib", std::ios::in | std::ios::binary);
	std::ifstream inputFile("bibfile.bib", std::ios::in | std::ios::binary);
	std::ofstream outputFile("test2.bib", std::ios::out | std::ios::trunc | std::ios::binary);

	// utf8 symbols may take up to 6 bytes, but Russian symbols are 2 bytes.
	char character[2];//, chraracterTemp, *firstPartOfChar, *secondPartOfChar, *thirdPartOfChar, *fourthPartOfChar;

	char utf8BOM[3];
	utf8BOM[0] = 0xEF;
	utf8BOM[1] = 0xBB;
	utf8BOM[2] = 0xBF;

	char mask1 = 0b10000000; //0b01111111;
	char mask2 = 0b11000000; //001111111;
	char mask3 = 0b11100000; //000111111;
	char16_t maskForSecondByte = 0b0000000011111111;

	char utf8TwoByteCharacterTemplateFirstPart = 0b11000000;
	char utf8TwoByteCharacterTemplateSecondPart = 0b10000000;


	//for( int k = 0; k < 10 ; ++k)
		//inputFile.read(firstPartOfChar, 1);

	i = 0;
	bool is_utf8 = true;
	while(!inputFile.eof() && is_utf8 && i < 3)
	{
		inputFile.read(character, 1);
		is_utf8 = utf8BOM[i] == *character;
		++i;
	};



	if (is_utf8)
	{
		int j; // For loop to print symbols from rusToEngTransliterationAlphabet.
		bool allSymbolsPrinted;

		while(!inputFile.eof())
		{
			inputFile.read(character, 1);

			//auto test = *character ^ mask1;
			if (*character & mask1)
			{
				if ((*character & mask3) == utf8TwoByteCharacterTemplateFirstPart)
				{
					if (!inputFile.eof())
					{
						inputFile.read(character + 1, 1);

						//int tempChar = 0;
						//int testInt = 42 << 8;
						//int tempCharInt1, tempCharInt2; char tempChar2;
						//tempCharInt1 = character[0];
						///tempChar2 = character[0];
						//tempCharInt2 = tempChar2;
						//int tempChar4 = *(character + 0);
						///int tempChar2 = tempChar << 8;
						//int tampChar3 = *character;
						//auto temp5 = ((character[0])<<8) + character[1];
						//auto temp6 = (character[0]) << 8;
						//auto temp7 = *(character + 0) << 8;
						//tempChar2 <<= 8;
						//tempChar2 <<= 8;
						//tempChar2 += character[1] ;// << 8;//+ character[1];
						//auto test2 = test + character[1];
						//i = FindCharacterIndexInArray( ((character[0])<<8) + character[1], rusAlphabet, 66);
						//i = FindCharacterIndexInArray( (static_cast<char16_t>(character[0])<<8) + character[1], rusAlphabet, 66);
						//i = FindCharacterIndexInArray( (tempChar <<  8) + character[1], rusAlphabet, 66);
						//char tempChar;
						//tempChar = static_cast<int>(character[0]);



						//char16_t tempCharWithShift1 = static_cast<char16_t>(character[0]) << 8;
						//char16_t tempCharWithShift2 = static_cast<char16_t>(character[1]);
						//tempCharWithShift2 &= maskForSecondByte;
						char16_t tempChar1, tempChar2;//, tempChar3;


						tempChar2 = (static_cast<char16_t>(character[0]) << 8) + (static_cast<char16_t>(character[1]) & maskForSecondByte); //tempCharWithShift1 + tempCharWithShift2;
						//tempChar = (static_cast<int>(character[0]) << 8) + character[1];
						std::memcpy( &tempChar1, character, 2);

						i = FindCharacterIndexInArray( tempChar2, rusAlphabet, 66);

						j = 0;
						allSymbolsPrinted = false;

						while(!allSymbolsPrinted)
						{
							outputFile.write(&rusToEngTransliterationAlphabet[i][j], 1);
							++j;
							if(rusToEngTransliterationAlphabet[i][j] == '\0')
							{
								allSymbolsPrinted = true;
							};
						};
					}
					else
					{
						outputFile.write(character, 1); // End of file reached, probably corrupt input file. Just copying.
					};
				}
				else
				{
					outputFile.write(character, 1); // Unexpected symbol code, certainly not Russian. Just copying.
				};

			}
			else
			{
				// ASCII
				outputFile.write(character, 1); // Copying ASCII symbol.
			};
		};
	}
	else
	{
		const char message[] = "No UTF8 BOM (Byte Order Mark) found.";

		outputFile.write(message, 37);
	};
	//inputFile.read(firstPartOfChar, 1);

	inputFile.close();
	outputFile.flush();
	outputFile.close();

	return 0;
}

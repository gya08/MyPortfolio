typedef volatile unsigned short hword;
#define VRAM 0x06000000
#define BGR(r, g, b) ((b << 10) + (g << 5) + r)

int myN[3];
int opN[3];
int wnr;
void wait(int);
void draw_point(hword, hword, hword);
void draw_number(hword, hword, hword, hword, hword, hword, hword);
void draw_basic(hword);
void change_number(hword, hword, int, hword);
void blink_red(int, int, hword, hword);
int select_number(int, int, int, hword, hword, hword);
int judge_eat(int, int, int, int, int, int);
int judge_byte(int, int, int, int, int, int);
int guess_number(int, int, int, int, int, int, hword, hword, hword);
void draw_winner(int, hword);

int main(void)
{
	hword *ptr;
	hword *ptr1;
	ptr = (hword*)0x04000000;
	*ptr = 0x0F03;
	ptr1 = (hword*)0x04000130;
	hword colorBc;
	colorBc = 0x0000;
	hword colorW;
	colorW = 0x7FFF;
	hword colorR;
	colorR = 0x001F;

	int i = 0;
	for(i=0; i<38400; i++){
		ptr = (hword*)(VRAM + 2*i);
		*ptr = colorW;
	}

	draw_basic(colorBc);

	int h = 0;
	while(1){
		for(h = 0; h < 3; h++){
			myN[h] = select_number((40 + h*16), 4, 1, colorBc, colorW, colorR);
			wait(100000);
		}

		if((myN[0] != myN[1]) && (myN[0] != myN[2]) && (myN[1] != myN[2])){
			break;
		}
	}

	for(h = 0; h < 3; h++){
		change_number((40 + h*16), 4, myN[h], colorW);
	}
	wait(100000);

	while(1){
		for(h = 0; h < 3; h++){
			opN[h] = select_number((160 + h*16), 4, 1, colorBc, colorW, colorR);
			wait(100000);
		}

		if((opN[0] != opN[1]) && (opN[0] != opN[2]) && (opN[1] != opN[2])){
			break;
		}
	}

	for(h = 0; h < 3; h++){
		change_number((160 + h*16), 4, opN[h], colorW);
	}
	wait(1000000);


	int myN1 = myN[0];
	int myN2 = myN[1];
	int myN3 = myN[2];
	int opN1 = opN[0];
	int opN2 = opN[1];
	int opN3 = opN[2];
	wnr = guess_number(myN1, myN2, myN3, opN1, opN2, opN3, colorBc, colorW, colorR);
	wait(100000);

	for(h = 0; h < 3; h++){
		change_number((40 + h*16), 4, myN[h], colorBc);
		change_number((160 + h*16), 4, opN[h], colorBc);
	}
	wait(100000);
	draw_winner(wnr, colorR);
	while(1);
	return 0;
}

void wait(int a){
	int i;
	int sum;
	for(i = 0; i < a; i++){
		for(i = 0; i < a; i++){
			for(i = 0; i < a; i++){
				for(i = 0; i < a; i++){
					for(i = 0; i < a; i++){
						sum += i * a;
					}
				}
			}
		}
	}
}

void draw_point(hword x, hword y, hword color){
	hword *ptr2;
	ptr2 = (hword*)VRAM + (y-1)*240+x;
	*ptr2 = color;
}

void draw_number(hword x, hword y, hword pack2, hword pack1, hword pack4, hword pack3, hword color){
	int l;
	int m;
	int tx;
	int ty;

	ty = y;
	hword tpack1;
	tpack1 = pack1;
	for (l = 1; l <= 2; l++) {
		tx = x;
		for (m = 1; m <= 8; m++) {
			hword chpack1;
			chpack1 = tpack1 & 0x0001;
			if(chpack1 == 0x0001){
				draw_point(tx, ty, color);
			}
			tpack1 = tpack1 >> 1;
			tx = tx + 1;
			if(m == 8){
				ty = ty + 1;
			}
		}
	}

	hword tpack2;
	tpack2 = pack2;
	for (l = 1; l <= 2; l++) {
		tx = x;
		for (m = 1; m <= 8; m++) {
			hword chpack2;
			chpack2 = tpack2 & 0x0001;
			if(chpack2 == 0x0001){
				draw_point(tx, ty, color);
			}
			tpack2 = tpack2 >> 1;
			tx = tx + 1;
			if(m == 8){
				ty = ty + 1;
			}
		}
	}

	hword tpack3;
	tpack3 = pack3;
	for (l = 1; l <= 2; l++) {
		tx = x;
		for (m = 1; m <= 8; m++) {
			hword chpack3;
			chpack3 = tpack3 & 0x0001;
			if(chpack3 == 0x0001){
				draw_point(tx, ty, color);
			}
			tpack3 = tpack3 >> 1;
			tx = tx + 1;
			if(m == 8){
				ty = ty + 1;
			}
		}
	}

	hword tpack4;
	tpack4 = pack4;
	for (l = 1; l <= 2; l++) {
		tx = x;
		for (m = 1; m <= 8; m++) {
			hword chpack4;
			chpack4 = tpack4 & 0x0001;
			if(chpack4 == 0x0001){
				draw_point(tx, ty, color);
			}
			tpack4 = tpack4 >> 1;
			tx = tx + 1;
			if(m == 8){
				ty = ty + 1;
			}
		}
	}
}

void change_number(hword x, hword y, int number, hword color){
	if(number == 0){
		draw_number(x, y, 0x7E76, 0x663C, 0x003C, 0x666E, color);
	}else if(number == 1){
		draw_number(x, y, 0x181E, 0x1C18, 0x0018, 0x1818, color);
	}else if(number == 2){
		draw_number(x, y, 0x3060, 0x663C, 0x007E, 0x0C18, color);
	}else if(number == 3){
		draw_number(x, y, 0x3860, 0x663C, 0x003C, 0x6660, color);
	}else if(number == 4){
		draw_number(x, y, 0x3336, 0x3C38, 0x0030, 0x307F, color);
	}else if(number == 5){
		draw_number(x, y, 0x603E, 0x067E, 0x003C, 0x6660, color);
	}else if(number == 6){
		draw_number(x, y, 0x3E06, 0x0C38, 0x003C, 0x6666, color);
	}else if(number == 7){
		draw_number(x, y, 0x3060, 0x607E, 0x0018, 0x1818, color);
	}else if(number == 8){
		draw_number(x, y, 0x3C66, 0x663C, 0x003C, 0x6666, color);
	}else if(number == 9){
		draw_number(x, y, 0x7C66, 0x663C, 0x001C, 0x3060, color);
	}
}

void blink_red(int l, int j, hword color1, hword color2){
	if(j == 1){
		
		draw_number(l, 12, 0x0000, 0x0000, 0x003F, 0x0000, color1);
		wait(1);
		draw_number(l, 12, 0x0000, 0x0000, 0x003F, 0x0000, color2);
	}
}

int select_number(int x, int y, int j, hword color1, hword color2, hword color3){
	
	hword *ptrx;
	ptrx = (hword*)0x04000130;
	int a = 0;
	draw_number(x, y, 0x7E76, 0x663C, 0x003C, 0x666E, color1);

	while(1){
		blink_red(x, j, color3, color1);
		if(((*ptrx & 0x0020) == 0x0000) && (a>0)){
			
			change_number(x, y, a, color2);
			a = a - 1;
			change_number(x, y, a, color1);
			wait(100000);
		}else if(((*ptrx & 0x0010) == 0x0000) && (a<9)){
			
			change_number(x, y, a, color2);
			a = a + 1;
			change_number(x, y, a, color1);
			wait(100000);
		}else if(((*ptrx & 0x0010) == 0x0000) && (a==9)){
			
		}else if((*ptrx & 0x0001) == 0x0000){
			
			wait(100000);
			break;
		}
	}
	return a;
}

void draw_basic(hword color){
	
	int j;
	for(j = 0; j <160; j++){draw_number(120, j, 0x1818, 0x1818, 0x1818, 0x1818, color);
	}
	int k;
	for(k = 0; k < 3; k++){
		
		draw_number((40 + 16*k), 12, 0x0000, 0x0000, 0x003F, 0x0000, color);
		draw_number((160 + 16*k), 12, 0x0000, 0x0000, 0x003F, 0x0000, color);
	}
	
	draw_number(32, 26, 0x6B7F, 0x7763, 0x0063, 0x6363, color);
	draw_number(40, 26, 0x6666, 0x0000, 0x0C18, 0x3C66, color);
	draw_number(48, 26, 0x3C0E, 0x663C, 0x003C, 0x6670, color);
	draw_number(56, 26, 0x063C, 0x0000, 0x003C, 0x0606, color);
	draw_number(64, 26, 0x663E, 0x0000, 0x0006, 0x0606, color);
	draw_number(72, 26, 0x1E06, 0x067E, 0x007E, 0x0606, color);
	draw_number(80, 26, 0x3E66, 0x663E, 0x003E, 0x6666, color);
	
	draw_number(152, 26, 0x6666, 0x663C, 0x003C, 0x6666, color);
	draw_number(160, 26, 0x663E, 0x0000, 0x0606, 0x3E66, color);
	draw_number(168, 26, 0x3C0E, 0x663C, 0x003C, 0x6670, color);
	draw_number(176, 26, 0x063C, 0x0000, 0x003C, 0x0606, color);
	draw_number(184, 26, 0x663E, 0x0000, 0x0006, 0x0606, color);
	draw_number(192, 26, 0x1E06, 0x067E, 0x007E, 0x0606, color);
	draw_number(200, 26, 0x3E66, 0x663E, 0x003E, 0x6666, color);
}

int judge_eat(int gss1, int gss2, int gss3, int num1, int num2, int num3){
	int eat = 0;
	if(gss1 == num1){
		eat += 1;
	}
	if(gss2 == num2){
		eat += 1;
	}
	if(gss3 == num3){
		eat += 1;
	}
	return eat;
}

int judge_byte(int gss1, int gss2, int gss3, int a1, int a2, int a3){
	int byte = 0;
	if(gss1 == a2){
		byte = byte + 1;
	}
	if(gss1 == a3){
		byte = byte + 1;
	}
	if(gss2 == a1){
		byte = byte + 1;
	}
	if(gss2 == a3){
		byte = byte + 1;
	}
	if(gss3 == a1){
		byte = byte + 1;
	}
	if(gss3 == a2){
		byte = byte + 1;
	}
	return byte;
}

int guess_number(int a1, int a2, int a3, int r1, int r2, int r3, hword color, hword color1, hword color2){
	
	int e;
	int b;
	int gss1;
	int gss2;
	int gss3;
	int winner;
	int myGss[3];
	int opGss[3];
	
	int turn = 0;
	
	int mycount = 0;
	int opcount = 0;
	while(e != 3){
		if(opcount == 10){
			winner = 3;
			break;
		}
		if(turn == 0){
			
			change_number(40, 0, a1, color);
			change_number(56, 0, a2, color);
			change_number(72, 0, a3, color);
			int g;
			while(1){
				for(g = 0; g < 3; g++){
					myGss[g] = select_number((48 + g*8), (34+8*mycount), 0, color, color1, color2);
					wait(100000);
				}

				if((myGss[0] != myGss[1]) && (myGss[0] != myGss[2]) && (myGss[1] != myGss[2])){
					break;
				}
			}
			
			gss1 = myGss[0];
			gss2 = myGss[1];
			gss3 = myGss[2];
			e = judge_eat(gss1, gss2, gss3, r1, r2, r3);
			change_number(72, (34+8*mycount), e, color);
			b = judge_byte(gss1, gss2, gss3, r1, r2, r3);
			change_number(80, (34+8*mycount), b, color);
			wait(100000);
			
			change_number(40, 0, a1, color1);
			change_number(56, 0, a2, color1);
			change_number(72, 0, a3, color1);
			if(e == 3){
				winner = 0;
			}
			wait(2000000);
			turn++;
			mycount++;
		}else{
			
			change_number(160, 0, r1, color);
			change_number(178, 0, r2, color);
			change_number(194, 0, r3, color);
			int f;
			while(1){
				for(f = 0; f < 3; f++){
					opGss[f] = select_number((166 + f*8), (34+8*opcount), 0, color, color1, color2);
					wait(100000);
				}

				if((opGss[0] != opGss[1]) && (opGss[0] != opGss[2]) && (opGss[1] != opGss[2])){
					break;
				}
			}

			
			gss1 = opGss[0];
			gss2 = opGss[1];
			gss3 = opGss[2];
			e = judge_eat(gss1, gss2, gss3, a1, a2, a3);
			change_number(192, (34+8*opcount), e, color);
			b = judge_byte(gss1, gss2, gss3, a1, a2, a3);
			change_number(200, (34+8*opcount), b, color);
			wait(100000);
			
			change_number(160, 0, r1, color1);
			change_number(178, 0, r2, color1);
			change_number(194, 0, r3, color1);
			if(e == 3){
				winner = 1;
			}
			wait(2000000);
			turn--;
			opcount++;
		}
	}
	return winner;
}

void draw_winner(int wnr, hword color){
	if(wnr == 0){
		
		draw_number(112, 26, 0x6B63, 0x6363, 0x0063, 0x777F, color);
		draw_number(112, 42, 0x1818, 0x183C, 0x003C, 0x1818, color);
		draw_number(112, 58, 0x7B6F, 0x6763, 0x0063, 0x6373, color);
	}else if(wnr == 1){
		
		draw_number(128, 26, 0x6B63, 0x6363, 0x0063, 0x777F, color);
		draw_number(128, 42, 0x1818, 0x183C, 0x003C, 0x1818, color);
		draw_number(128, 58, 0x7B6F, 0x6763, 0x0063, 0x6373, color);
	}else if(wnr == 3){
		
		draw_number(120, 26, 0x6666, 0x361E, 0x001E, 0x3666, color);
		draw_number(120, 42, 0x3E66, 0x663E, 0x0066, 0x6636, color);
		draw_number(120, 58, 0x7E66, 0x663C, 0x0066, 0x6666, color);
		draw_number(120, 74, 0x6B63, 0x6363, 0x0063, 0x777F, color);
	}
}

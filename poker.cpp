#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct CARD { // 카드의 정보를 가지는 구조체 CARD 정의
	int suit; // suit는 1~4의 값을 가진다. 1이 스페이드 2가 클로버 3이 하트 4가 다이아몬드의 값을 가진다고 생각
	int rank; // rank는 1~13까지의 값을 가진다. 11, 12, 13은 각각 J Q K다
	int indeck = 0; // 해당 카드가 덱에 있는지 여부를 알 수 있는 변수 indeck. indeck = 0 이면 덱에, indeck = 1이면 패에 해당 카드가 존재한다.
};

struct PLAYER { // 플레이어의 정보를 가지는 구조체 PLAYER 정의
	int win = 0, lose = 0, draw = 0; // win, lose, draw는 각각의 승리 횟수, 패배 횟수, 무승부 횟수를 저장.
	struct CARD *hand[5]; // 플레이어의 패의 정보를 나타내는 hand.  5장씩 나눠 가지기 때문에 크기가 5
};

void init_deck(CARD* deck) { // 덱을 초기화 하는 함수 init_deck
	for (int i = 0; i < 52; i++) { // 덱에 있는 카드에 suit 와 rank 값을 부여한다.
		deck[i].suit = i % 4 + 1;
		deck[i].rank = i % 13 + 1;
	}
}

void shuffle_deck(CARD* deck) { // 덱을 섞는 함수 shuffle_deck
	struct CARD temp;
	int num;
	for (int i = 0; i < 52; i++) { // 덱에 존재하는 각각의 카드에 대해 0 ~ 51의 난수를 생성하여 그 수를 index 값으로 가지는 카드와 자리를 바꾸는 방식으로 덱을 섞는다.
		num = rand() % 52;
		temp = deck[i];
		deck[i] = deck[num];
		deck[num] = temp;
	}
}

CARD* getCard(CARD* deck) { // 플레이어에게 카드를 나눠주는 함수 getCard
	int check = 0;
	while (deck[check].indeck == 1) {
		check++;
	}
	deck[check].indeck = 1;
	return &deck[check];
}

void returnCard(CARD* deck) { // 플레이어가 가지고 있는 카드를 덱으로 반환 하는 함수 returnCard
	for (int i = 0; i< 10; i++) { // 패에 있는 카드의 indeck 값을 0으로 바꾸는 방식으로 덱에 반환한다.
		deck[i].indeck = 0;
	}
	}

int score(CARD** hand); // 플레이어의 패를 인자로 받아 얼마나 강한 조합인지를 return 하는 함수 (1 ~ 8 의 값을 리턴하는데 값이 작을수록 카드가 강한 조합)

int decideWinner(CARD** player1_cards, CARD** player2_cards) { // score 함수를 이용해 플레이어 각각의 패를 비교해 승자를 판별하는 함수
	int myscore, comscore;
	printf("\n플레이어 - "); // 사용자도 알 수 있게 플레이어와 컴퓨터의 패 조합을 출력
	myscore = score(player1_cards);
	printf("\n컴퓨터 - ");
	comscore = score(player2_cards);
	printf("\n");
	if (myscore < comscore) { // 플레이어가 이기면 1을, 컴퓨터가 이기면 2를, 비기면 0을 리턴한다.
		return 1;
	}
	else if (myscore == comscore) {
		return 0;
	}
	else return 2;
}

void printhand(CARD** hand) { // 패를 입력받아 패에 있는 카드의 정보를 출력하는 함수 printhand
	for (int i = 0; i < 5; i++) { 
		if (hand[i]->suit == 1) { // 패에 있는 카드의 suit를 확인하고 해당하는 suit 출력
			printf("스페이드 ");
		}
		else if (hand[i]->suit == 2) {
			printf("클로버 ");
		}
		else if (hand[i]->suit == 3) {
			printf("하트 ");
		}
		else if (hand[i]->suit == 4) {
			printf("다이아몬드 ");
		}

		if (hand[i]->rank == 1) { // 패에 있는 카드의 rank를 확인하고 해당하는 rank 출력
			printf("에이스\n");
		}
		else if (hand[i]->rank == 2) {
			printf("2\n");
		}
		else if (hand[i]->rank == 3) {
			printf("3\n");
		}
		else if (hand[i]->rank == 4) {
			printf("4\n");
		}
		else if (hand[i]->rank == 5) {
			printf("5\n");
		}
		else if (hand[i]->rank == 6) {
			printf("6\n");
		}
		else if (hand[i]->rank == 7) {
			printf("7\n");
		}
		else if (hand[i]->rank == 8) {
			printf("8\n");
		}
		else if (hand[i]->rank == 9) {
			printf("9\n");
		}
		else if (hand[i]->rank == 10) {
			printf("10\n");
		}
		else if (hand[i]->rank == 11) {
			printf("잭\n");
		}
		else if (hand[i]->rank == 12) {
			printf("퀸\n");
		}
		else if (hand[i]->rank == 13) {
			printf("킹\n");
		}
	}
}

int main() {
	srand((unsigned int)time(NULL)); // 난수 초기화
	struct CARD deck[52]; // 52장의 카드를 가지는 덱(구조체의 배열) 선언
	struct PLAYER player, computer; // 사용자와 컴퓨터 각각의 정보를 저장하는 PLAYER 구조체 선언
	char end = 'a'; // 플레이어가 계속 해서 플레이하고 싶은지 여부를 입력받아 저장하는 변수 end, x를 입력하면 프로그램을 종료한다.
	int winorlose; // 승자가 누구인지 정보를 저장하는 변수 winorlose, 1이면 플레이어가 승, 2면 컴퓨터가 승, 0이면 무승부다.
	
	
	while (1) { // 사용자가 x를 입력할 때 까지 계속해서 반복
		init_deck(deck); // 매 판이 시작될 때 마다 덱 초기화
		shuffle_deck(deck); // 매 판마다 덱을 섞는다.
		for (int turn = 0; turn < 5; turn++) { // 각각의 플레이어에게 1장씩 5번 총 5장의 카드를 나눠준다
			player.hand[turn] = getCard(deck);
			computer.hand[turn] = getCard(deck);
		}
		
		winorlose = decideWinner(player.hand, computer.hand); // 부여받은 패로 어떤 플레이어가 이겼는지 판단
		if (winorlose == 1) { // winorlose가 1이면 플레이어 승
			printf("플레이어 승!\n");
			player.win++;
			computer.lose++;
		}
		else if (winorlose == 2) { // winorlose가 2이면 컴퓨터 승
			printf("컴퓨터 승!\n");
			player.lose++;
			computer.win++;
		}
		else if (winorlose == 0) { // winorlose가 0이면 무승부
			printf("무승부!\n");
			player.draw++;
			computer.draw++;
		}
		// 각각의 플레이어가 가진 패를 출력
		printf("\n플레이어 패:\n"); // 플레이어의 패를 출력
		printhand(player.hand);
		printf("\n컴퓨터 패:\n"); // 컴퓨터의 패를 출력
		printhand(computer.hand);
		returnCard(deck);
		printf("\n끝내고 싶으면 x를 입력하세요. 그 외의 버튼을 입력하면 계속해서 진행됩니다: ");
		rewind(stdin);
		scanf("%c", &end); // 플레이어가 게임을 끝내고 싶은지 정보를 입력받아 end에 저장, x를 입력하면 게임을 끝내고 그 외에는 게임 진행
		if (end == 'x') {
			break;
		}
	}
	// 사용자의 승리 횟수, 패배 횟수, 무승부 횟수를 출력
	printf("\n승리 횟수: %d, 패배 횟수: %d, 무승부 횟수: %d", player.win, player.lose, player.draw);

	return 0;
}

int score(CARD** hand) { // 패를 인자로 받아 얼마나 강한 패인지 return 하는 함수, hand 값이 작을수록 강한 패다, 플레이어도 확인할 수 있게 인자로 받은 패의 조합을 출력한다.
	for (int i = 4; i > 0; i--) { // 패에 있는 카드의 rank를 기준으로 오름차순으로 배열 (스트레이트 판별을 용이하게 하고 사용자도 확인하기 편하게 하기 위하여)
		for (int j = 0; j < i; j++) {
			struct CARD* temp;
			if (hand[j]->rank > hand[j + 1]->rank) {
				temp = hand[j];
				hand[j] = hand[j + 1];
				hand[j + 1] = temp;
			}
		}
	}
	int rankcount = 0; // 5장의 카드를 각각 비교하여 rank가 같은 횟수를 저장하는 rankcount
	int suitcount = 0; // 5장의 카드를 각각 비교하여 suit가 같은 횟수를 저장하는 suitcount
	for (int i = 0; i < 5; i++) { // 카드를 비교하여 rankcount와 suitcount에 값을 부여
		for (int j = i + 1; j < 5; j++) {
			if (hand[i]->rank == hand[j]->rank) {
				rankcount++;
			}
			if (hand[i]->suit == hand[j]->suit) {
				suitcount++;
			}
		}
	}
	if (rankcount == 6) { // rankcount가 6이면 4장의 rank가 같다 => 포카드
		printf("포카드\n");
		return 1;
	}
	else if (rankcount == 4) { // rankcount가 4이면 각각 3장과 2장의 rank가 같다 => 풀하우스
		printf("풀하우스\n");
		return 2;
	}
	else if (suitcount == 10) { // 모든 카드의 suit가 같다 => 플래쉬
		printf("플래쉬\n");
		return 3;
	}
	else if (hand[0]->rank == 1 && rankcount == 0) { // 10 J Q K A 라는 예외적 상황에 대한 처리
		if (hand[4]->rank == 13 && hand[1]->rank == 10) { // rank에 대해 오름차순으로 카드를 배열하고 겹치는 카드가 없다면
			printf("스트레이트\n");                       // 그리고 가장 큰 수가 13, 2번째로 작은 수가 10이면 10 J Q K A에 해당한다
			return 4;
		}
		printf("x\n"); // 10 J Q K A 가 아닌 패는 조합이 없다
		return 8;
	}
	else if (rankcount == 0 && hand[4]->rank - hand[0]->rank == 4) {
		printf("스트레이트\n");
		return 4; // 겹치는 숫자가 없고 인접한 카드끼리의 rank의 차가 1이면 스트레이트
	}
	else if (rankcount == 3) { // rankcount가 3이면 3장의 rank가 같다 => 트리플
		printf("트리플\n");
		return 5;
	}
	else if (rankcount == 2) { // rankcount가 2이면 각각 2장씩의 rank가 같다 => 투페어
		printf("투페어\n");
		return 6;
	}
	else if (rankcount == 1) { // rankcount가 1이면 2장의 rank만 같다
		printf("원페어\n");
		return 7;
	}
	else { // 해당하는 경우가 없다면 가장 약한 조합 ( 해당하는 조합 x )
		printf("x\n");
		return 8;
	}
}
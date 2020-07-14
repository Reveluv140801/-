#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct CARD { // ī���� ������ ������ ����ü CARD ����
	int suit; // suit�� 1~4�� ���� ������. 1�� �����̵� 2�� Ŭ�ι� 3�� ��Ʈ 4�� ���̾Ƹ���� ���� �����ٰ� ����
	int rank; // rank�� 1~13������ ���� ������. 11, 12, 13�� ���� J Q K��
	int indeck = 0; // �ش� ī�尡 ���� �ִ��� ���θ� �� �� �ִ� ���� indeck. indeck = 0 �̸� ����, indeck = 1�̸� �п� �ش� ī�尡 �����Ѵ�.
};

struct PLAYER { // �÷��̾��� ������ ������ ����ü PLAYER ����
	int win = 0, lose = 0, draw = 0; // win, lose, draw�� ������ �¸� Ƚ��, �й� Ƚ��, ���º� Ƚ���� ����.
	struct CARD *hand[5]; // �÷��̾��� ���� ������ ��Ÿ���� hand.  5�徿 ���� ������ ������ ũ�Ⱑ 5
};

void init_deck(CARD* deck) { // ���� �ʱ�ȭ �ϴ� �Լ� init_deck
	for (int i = 0; i < 52; i++) { // ���� �ִ� ī�忡 suit �� rank ���� �ο��Ѵ�.
		deck[i].suit = i % 4 + 1;
		deck[i].rank = i % 13 + 1;
	}
}

void shuffle_deck(CARD* deck) { // ���� ���� �Լ� shuffle_deck
	struct CARD temp;
	int num;
	for (int i = 0; i < 52; i++) { // ���� �����ϴ� ������ ī�忡 ���� 0 ~ 51�� ������ �����Ͽ� �� ���� index ������ ������ ī��� �ڸ��� �ٲٴ� ������� ���� ���´�.
		num = rand() % 52;
		temp = deck[i];
		deck[i] = deck[num];
		deck[num] = temp;
	}
}

CARD* getCard(CARD* deck) { // �÷��̾�� ī�带 �����ִ� �Լ� getCard
	int check = 0;
	while (deck[check].indeck == 1) {
		check++;
	}
	deck[check].indeck = 1;
	return &deck[check];
}

void returnCard(CARD* deck) { // �÷��̾ ������ �ִ� ī�带 ������ ��ȯ �ϴ� �Լ� returnCard
	for (int i = 0; i< 10; i++) { // �п� �ִ� ī���� indeck ���� 0���� �ٲٴ� ������� ���� ��ȯ�Ѵ�.
		deck[i].indeck = 0;
	}
	}

int score(CARD** hand); // �÷��̾��� �и� ���ڷ� �޾� �󸶳� ���� ���������� return �ϴ� �Լ� (1 ~ 8 �� ���� �����ϴµ� ���� �������� ī�尡 ���� ����)

int decideWinner(CARD** player1_cards, CARD** player2_cards) { // score �Լ��� �̿��� �÷��̾� ������ �и� ���� ���ڸ� �Ǻ��ϴ� �Լ�
	int myscore, comscore;
	printf("\n�÷��̾� - "); // ����ڵ� �� �� �ְ� �÷��̾�� ��ǻ���� �� ������ ���
	myscore = score(player1_cards);
	printf("\n��ǻ�� - ");
	comscore = score(player2_cards);
	printf("\n");
	if (myscore < comscore) { // �÷��̾ �̱�� 1��, ��ǻ�Ͱ� �̱�� 2��, ���� 0�� �����Ѵ�.
		return 1;
	}
	else if (myscore == comscore) {
		return 0;
	}
	else return 2;
}

void printhand(CARD** hand) { // �и� �Է¹޾� �п� �ִ� ī���� ������ ����ϴ� �Լ� printhand
	for (int i = 0; i < 5; i++) { 
		if (hand[i]->suit == 1) { // �п� �ִ� ī���� suit�� Ȯ���ϰ� �ش��ϴ� suit ���
			printf("�����̵� ");
		}
		else if (hand[i]->suit == 2) {
			printf("Ŭ�ι� ");
		}
		else if (hand[i]->suit == 3) {
			printf("��Ʈ ");
		}
		else if (hand[i]->suit == 4) {
			printf("���̾Ƹ�� ");
		}

		if (hand[i]->rank == 1) { // �п� �ִ� ī���� rank�� Ȯ���ϰ� �ش��ϴ� rank ���
			printf("���̽�\n");
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
			printf("��\n");
		}
		else if (hand[i]->rank == 12) {
			printf("��\n");
		}
		else if (hand[i]->rank == 13) {
			printf("ŷ\n");
		}
	}
}

int main() {
	srand((unsigned int)time(NULL)); // ���� �ʱ�ȭ
	struct CARD deck[52]; // 52���� ī�带 ������ ��(����ü�� �迭) ����
	struct PLAYER player, computer; // ����ڿ� ��ǻ�� ������ ������ �����ϴ� PLAYER ����ü ����
	char end = 'a'; // �÷��̾ ��� �ؼ� �÷����ϰ� ������ ���θ� �Է¹޾� �����ϴ� ���� end, x�� �Է��ϸ� ���α׷��� �����Ѵ�.
	int winorlose; // ���ڰ� �������� ������ �����ϴ� ���� winorlose, 1�̸� �÷��̾ ��, 2�� ��ǻ�Ͱ� ��, 0�̸� ���ºδ�.
	
	
	while (1) { // ����ڰ� x�� �Է��� �� ���� ����ؼ� �ݺ�
		init_deck(deck); // �� ���� ���۵� �� ���� �� �ʱ�ȭ
		shuffle_deck(deck); // �� �Ǹ��� ���� ���´�.
		for (int turn = 0; turn < 5; turn++) { // ������ �÷��̾�� 1�徿 5�� �� 5���� ī�带 �����ش�
			player.hand[turn] = getCard(deck);
			computer.hand[turn] = getCard(deck);
		}
		
		winorlose = decideWinner(player.hand, computer.hand); // �ο����� �з� � �÷��̾ �̰���� �Ǵ�
		if (winorlose == 1) { // winorlose�� 1�̸� �÷��̾� ��
			printf("�÷��̾� ��!\n");
			player.win++;
			computer.lose++;
		}
		else if (winorlose == 2) { // winorlose�� 2�̸� ��ǻ�� ��
			printf("��ǻ�� ��!\n");
			player.lose++;
			computer.win++;
		}
		else if (winorlose == 0) { // winorlose�� 0�̸� ���º�
			printf("���º�!\n");
			player.draw++;
			computer.draw++;
		}
		// ������ �÷��̾ ���� �и� ���
		printf("\n�÷��̾� ��:\n"); // �÷��̾��� �и� ���
		printhand(player.hand);
		printf("\n��ǻ�� ��:\n"); // ��ǻ���� �и� ���
		printhand(computer.hand);
		returnCard(deck);
		printf("\n������ ������ x�� �Է��ϼ���. �� ���� ��ư�� �Է��ϸ� ����ؼ� ����˴ϴ�: ");
		rewind(stdin);
		scanf("%c", &end); // �÷��̾ ������ ������ ������ ������ �Է¹޾� end�� ����, x�� �Է��ϸ� ������ ������ �� �ܿ��� ���� ����
		if (end == 'x') {
			break;
		}
	}
	// ������� �¸� Ƚ��, �й� Ƚ��, ���º� Ƚ���� ���
	printf("\n�¸� Ƚ��: %d, �й� Ƚ��: %d, ���º� Ƚ��: %d", player.win, player.lose, player.draw);

	return 0;
}

int score(CARD** hand) { // �и� ���ڷ� �޾� �󸶳� ���� ������ return �ϴ� �Լ�, hand ���� �������� ���� �д�, �÷��̾ Ȯ���� �� �ְ� ���ڷ� ���� ���� ������ ����Ѵ�.
	for (int i = 4; i > 0; i--) { // �п� �ִ� ī���� rank�� �������� ������������ �迭 (��Ʈ����Ʈ �Ǻ��� �����ϰ� �ϰ� ����ڵ� Ȯ���ϱ� ���ϰ� �ϱ� ���Ͽ�)
		for (int j = 0; j < i; j++) {
			struct CARD* temp;
			if (hand[j]->rank > hand[j + 1]->rank) {
				temp = hand[j];
				hand[j] = hand[j + 1];
				hand[j + 1] = temp;
			}
		}
	}
	int rankcount = 0; // 5���� ī�带 ���� ���Ͽ� rank�� ���� Ƚ���� �����ϴ� rankcount
	int suitcount = 0; // 5���� ī�带 ���� ���Ͽ� suit�� ���� Ƚ���� �����ϴ� suitcount
	for (int i = 0; i < 5; i++) { // ī�带 ���Ͽ� rankcount�� suitcount�� ���� �ο�
		for (int j = i + 1; j < 5; j++) {
			if (hand[i]->rank == hand[j]->rank) {
				rankcount++;
			}
			if (hand[i]->suit == hand[j]->suit) {
				suitcount++;
			}
		}
	}
	if (rankcount == 6) { // rankcount�� 6�̸� 4���� rank�� ���� => ��ī��
		printf("��ī��\n");
		return 1;
	}
	else if (rankcount == 4) { // rankcount�� 4�̸� ���� 3��� 2���� rank�� ���� => Ǯ�Ͽ콺
		printf("Ǯ�Ͽ콺\n");
		return 2;
	}
	else if (suitcount == 10) { // ��� ī���� suit�� ���� => �÷���
		printf("�÷���\n");
		return 3;
	}
	else if (hand[0]->rank == 1 && rankcount == 0) { // 10 J Q K A ��� ������ ��Ȳ�� ���� ó��
		if (hand[4]->rank == 13 && hand[1]->rank == 10) { // rank�� ���� ������������ ī�带 �迭�ϰ� ��ġ�� ī�尡 ���ٸ�
			printf("��Ʈ����Ʈ\n");                       // �׸��� ���� ū ���� 13, 2��°�� ���� ���� 10�̸� 10 J Q K A�� �ش��Ѵ�
			return 4;
		}
		printf("x\n"); // 10 J Q K A �� �ƴ� �д� ������ ����
		return 8;
	}
	else if (rankcount == 0 && hand[4]->rank - hand[0]->rank == 4) {
		printf("��Ʈ����Ʈ\n");
		return 4; // ��ġ�� ���ڰ� ���� ������ ī�峢���� rank�� ���� 1�̸� ��Ʈ����Ʈ
	}
	else if (rankcount == 3) { // rankcount�� 3�̸� 3���� rank�� ���� => Ʈ����
		printf("Ʈ����\n");
		return 5;
	}
	else if (rankcount == 2) { // rankcount�� 2�̸� ���� 2�徿�� rank�� ���� => �����
		printf("�����\n");
		return 6;
	}
	else if (rankcount == 1) { // rankcount�� 1�̸� 2���� rank�� ����
		printf("�����\n");
		return 7;
	}
	else { // �ش��ϴ� ��찡 ���ٸ� ���� ���� ���� ( �ش��ϴ� ���� x )
		printf("x\n");
		return 8;
	}
}
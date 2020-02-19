#include <cstdlib>
#include <iostream>
#include <exception>
using namespace std;

class List {
public:
	struct Node {
		int	date{};
		Node* next{ nullptr };
	};

private:
	Node* m_front{ nullptr };
	Node* m_back{ nullptr };

	int m_listSize{ };

	void listCheck() {
		Node* member = m_front;
		for (int i = 0; i < m_listSize; i++) {
			if (member == nullptr) throw logic_error("ERR: error in resize list");
			member = member->next;
		}
	}

	Node* listSearch(int pos) const {
		if (pos >= m_listSize)		throw logic_error("ERR: out of range");
		if (pos < 0)				return nullptr;
		if (pos == 0)				return m_front;
		if (pos == m_listSize - 1)	return m_back;

		Node* member = m_front;

		for (int i = 0; i < pos; i++) {
			member = member->next;
		}

		return member;
	}

public:
	List() {

	}
	List(unsigned int listSize) {
		resize(listSize);
	}
	~List() {
		clear();
	}

	/* ������� ��� ����� ������ */
	void clear() {
		if (!isEmpty()) {
			Node* member = m_front;
			Node* nextMember;
			for (int i = 0; i < m_listSize; i++) {
				nextMember = member->next;
				delete member;
				member = nextMember;
			}
			m_front = nullptr;
			m_back = nullptr;
			m_listSize = 0;
		}
	}

	/* �������� ������ ������ ������ */
	void resize(int newListSize) {
		m_listSize = newListSize;

		if (!isEmpty()) {
			if (m_front == nullptr) { m_front = new Node; }

			Node* member = m_front;
			Node* nextMember = m_front->next;
			for (int i = 1; i < m_listSize; i++) {
				if (nextMember == nullptr) {
					member->next = new Node;
					nextMember = member->next;
				}
				member = nextMember;
				nextMember = member->next;
			}
			m_back = member;

			while (nextMember != nullptr) {
				member = nextMember;
				nextMember = member->next;
				delete member;
			}

			listCheck();
		}
	}

	/* ������� ������������� �������� ������ � ������� pos */
	int pos_back(int pos) const {
		Node* member = listSearch(pos);
		return member->date;
	}

	/* ���������� ������������� �������� ������ � ������� pos */
	List& set(int pos, int date) {
		Node* member = listSearch(pos);
		member->date = date;
		return (*this);
	}

	/* �������� ����� ���� ������ ����� ������� pos */
	List& push(int pos, int date = 0) {
		Node tmpNode{ 0, m_front };									// �����, �������������� ������� ����� 
		Node* member = (pos == -1) ? &tmpNode : listSearch(pos);	// �����, �������������� ������ �����	
		Node* nextMember = member->next;

		member->next = new Node;
		member->next->date = date;

		member->next->next = nextMember;
		if (nextMember == nullptr) { m_back = member->next; }
		if (pos < 0) { m_front = member->next; }
		++m_listSize;

		return (*this);
	}

	/* ������� ���� ������ �� �������� ������� pos */
	int remove(int pos) {
		if (isEmpty()) {
			throw logic_error("ERR list is empty!");
			return 0;
		}
		Node* prevMember = listSearch(pos - 1);
		if (prevMember != nullptr) {				// ���� ������ ����� ��������� �� � ������
			Node* member = prevMember->next;
			int date = member->date;

			prevMember->next = member->next;
			delete member;

			if (pos == m_listSize - 1) m_back = prevMember;
			--m_listSize;

			return date;
		}
		else {										//	if (prevMember != nullptr)									
			int date = m_front->date;
			Node* nextMember = m_front->next;
			delete m_front;

			m_front = nextMember;
			--m_listSize;

			return date;
		}
	}

	/* ���������� ������ ������ */
	unsigned int size() { return m_listSize; }

	/* ����������, ������ �� ������ ��� ��� */
	bool isEmpty() { return m_listSize == 0; }

	/* ��������� ����� ����� � ������ ������ */
	List& push_front(int date = 0) { return push(-1, date); }

	/* ��������� ����� ����� � ����� ������ */
	List& push_back(int date = 0) { return push(m_listSize - 1, date); }

	/* ���������� �������� � ��������� ����� ������ */
	int back() { return pos_back(m_listSize - 1); }

	/* ���������� �������� � ������ ����� ������ */
	int front() { return pos_back(0); }

	/* ������� ��������� ����� ������ */
	int pop_back() { return remove(m_listSize - 1); }

	/* ������� ������ ����� ������ */
	int pop_front() { return remove(0); }
};

int main() {
	system("chcp 1251"); system("cls");

	List list;
	constexpr auto SIZE = 1'000;
	for (int i = 0; i < SIZE; ++i) {
		list.push_front(i);
	}
	for (int i = 0; i < SIZE; ++i) {
		cout << list.pop_front() << "\t";
		if ((i + 1) % 10 == 0) cout << endl;
	}
	cout << endl;

	/*
		������ ������� ������ �������, ~3 �� ������, ������
	*/

	constexpr auto SIZE2 = 40'000'000;
	constexpr auto SIZE3 = 2'000'000;
	cout << "All: ";
	for (int i = 0; i < SIZE2; i += SIZE3) {
		cout << "[  ]";
	}
	cout << endl << "     ";

	for (int i = 0; i < SIZE2; ++i) {
		list.push_back(i);
		if (i % SIZE3 == 0) cout << " || ";
	}
	cout << endl;
	list.clear();

	cout << "All: ";
	for (int i = 0; i < SIZE2; i += SIZE3) {
		cout << "[  ]";
	}
	cout << endl << "     ";

	for (int i = 0; i < SIZE2; ++i) {
		list.push_back(i);
		if (i % SIZE3 == 0) cout << " || ";
	}
	cout << endl;
	list.clear();

	if (list.isEmpty()) cout << "���� ������!";
	else cout << "���� �� ������((";
	cout << endl;

	system("pause");
	return 0;
}
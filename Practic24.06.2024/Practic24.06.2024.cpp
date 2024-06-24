#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

/*
Написать программу «Автоматизированная информационная
система ЖД вокзала». Система содержит: сведения об
отправлении поездов дальнего следования. Для каждого
поезда указываем: номер, время отправления, станцию назначения. Обеспечить:
■ Ввод данных в систему;
■ Вывод информации о всех поездах;
■ Вывод информации о запрашиваемом поезде.
Использовать контейнерный класс vector
*/
struct Train {
	int number;
	string departureTime;
	string destinationStation;
};
class TrainCollection {
private:
	vector<Train> trains;

public:
	void addTrain(int n, string dT, string dS) {
		Train train;
		train.number = n;
		train.departureTime = dT;
		train.destinationStation = dS;

		trains.push_back(train);
	}
	istream& addTrain(istream& in) {
		Train train;
		in >> train.number
			>> train.departureTime
			>> train.destinationStation;

		trains.push_back(train);
		return in;
	}
	//void showTrain() {
	//	for (vector<Train>::iterator iter = trains.begin();
	//		iter != trains.end(); iter++) {
	//		cout << iter->number << ": "
	//			<< iter->departureTime << " "
	//			<< iter->destinationStation
	//			<< endl;
	//	}
	//}

	ostream& showTrain(ostream& out) {
		for (Train train : trains) {
			out << train.number << ": "
				<< train.departureTime << " "
				<< train.destinationStation
				<< endl;
		}
		return out;
	}
	ostream& showTrainByNumber(ostream& out, int num) {
		for (Train train : trains) {
			if (train.number == num)
			{
				out << train.number << ": "
					<< train.departureTime << " "
					<< train.destinationStation
					<< endl;

			}
		}
		return out;
	}

};

/*
Используя контейнер map реализовать программу – словарь.
Основные возможности:
■ поиск слова;
■ добавление, удаление, редактирование слов;
■ чтение и запись словаря в файл.
*/

class Dictionary {
	map<string, string> dictionary;
public:
	string searchWord(string key) {
		auto result = dictionary.find(key);
		if (result != dictionary.end()) {
			return result->second;
		}
		return "false";
	}
	bool addWord(string key, string value) {
		auto ret = dictionary.insert(make_pair(key, value));
		if (!ret.second) {
			return false;
		}
		return true;
	}
	bool deleteWord(string key) {
		if (dictionary.erase(key)) {
			return true;
		}
		return false;

	}
	bool updateWord(string key, string new_value) {
		auto result = dictionary.find(key);
		if (result != dictionary.end()) {
			result->second = new_value;
			return true;
		}
		return false;
	}

	void loadDictionary(string nameFile) {
		ifstream file(nameFile);
		if (file.is_open()) {
			string str;
			string sel = " : ";
			while (getline(file, str))
			{
				/*size_t pos = str.find(sel);
				string key = str.substr(0, pos);
				string val = str.substr(pos + sel.length());
				dictionary.insert(make_pair(key, val));*/


				string key;
				string val;
				istringstream istr(str);
				istr >> key >> sel >>val;
				dictionary.insert(make_pair(key, val));
			}
			cout << "Данные успешно загружены\n";
		}
		else {
			cerr << "Не удалось открыть файл для чтения\n";
		}
		file.close();
	}
	void saveDictionary(string nameFile) {
		ofstream file(nameFile);
		if (file.is_open()) {
			for (pair<string, string> elem : dictionary) {
				file << elem.first << " : " << elem.second << endl;
			}
			cout << "Все данные успешно записаны в файл\n";
		}
		else {
			cerr << "Ошибка. Не удалось открыть файл для записи\n";
		}
		file.close();
	}

	void showMap() {
		for (pair<string, string> item : dictionary) {
			cout << item.first << ": " << item.second << endl;
		}
	}
};

int main()
{
	/*TrainCollection trainColl;
	trainColl.addTrain(3, "8:00", "station 1");
	trainColl.addTrain(5, "11:00", "station 2");
	trainColl.addTrain(10, "10:00", "station 7");
	trainColl.addTrain(8, "15:00", "station 4");
	trainColl.addTrain(10, "14:00", "station 3");

	trainColl.addTrain(cin);

	trainColl.showTrain(cout);
	cout << endl;
	trainColl.showTrainByNumber(cout, 10);*/
	//setlocale(LC_ALL, "");
	Dictionary dict;
	//if (dict.addWord("первый", "first")) cout << "Ok" << endl;
	//if (dict.addWord("второй", "two")) cout << "Ok" << endl;
	//if (dict.addWord("кот", "cat")) cout << "Ok" << endl;
	//if (dict.addWord("собака", "dog")) cout << "Ok" << endl;
	//if (dict.addWord("дом", "house")) cout << "Ok" << endl;
	//dict.loadDictionary("text.txt");
	//dict.showMap();

	//if (dict.updateWord("второй", "second")) cout << "Ok" << endl;
	//dict.showMap();

	//if (dict.deleteWord("дом")) cout << "Ok" << endl;
	//dict.showMap();
	//cout << dict.searchWord("кот");
	//cout << dict.searchWord("дом");
	//dict.saveDictionary("text.txt");

	fstream file;
	file.open("text.txt", ios::in | ios::binary);
	file.read((char*)&dict, sizeof(dict));
	dict.showMap();
}

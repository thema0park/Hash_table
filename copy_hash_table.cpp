# include <random>
# include <ctime>
# include "hash_table_contents.h"

# define MAX_COUNT 500
# define MAX_LENGTH 5

string make_rad_str(int length){
		string hash_table = "";
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(0,25);
		for(int i = 0; i < length; i++)
		{
			hash_table += (char)('a'+dis(gen));
		}
		return hash_table;
	}

int main()
{
	vector<string> test_inputs;
	vector<string> test2;
	// 난수 생성..
	for(int i = 0; i < MAX_COUNT; i++)
	{
		string result = make_rad_str(MAX_LENGTH);
		test_inputs.push_back(result);
	}

	// 테스트 시작을 위해 테이블 초기화
	int cnt = 0;
	string key;
	string value;
	//cout << "key : ";
	//cin >> key;
	//cout << "value : ";
	//cin >> value;
	my_map<string, string> hash_table(test_inputs[0], test_inputs[0]);
	///////////////////////////////////////////////////////////////////////////////////
	vector<string> test_case;
	test_case = {"clear","put","get","remove","replace","size","isEmpty","containsKey"
	,"containsValue","hashCode","KeySet","values","entrySet","rehashing","getOrDefault"
	,"putIfAbsent","replace"};
	///////////////////////////////////////////////////////////////////////////////////
	while(1){
		int num = 0;
		for(int i = 0; i < test_case.size(); i++)
		{
			cout << i << " : " << test_case[i] << endl;
		}
		cout << "테스트할 기능을 선택하세요.." << endl;
		cin >> num;
		switch(num)
		{
			case(0):
				cout << endl;
				cout << "clear test start.."  << endl;
				hash_table.my_clear();
				break;
			case(1):
			{
				/*cout << "put test start.."  << endl;
				cout << "key : ";
				cin >> key;
				cout << "value : ";
				cin >> value;
				hash_table.put(key,value); */
				//clock_t start, end , result;
				//start = clock(); // 시간 측정 시작
				for(int i = 1; i < test_inputs.size(); i++)
				{
					cout << i << " 번째 테스트 인풋은 " << test_inputs[i] << endl;
					hash_table.put(test_inputs[i],test_inputs[i]);
					cout << "end" << endl;
				}
			    	//end = clock(); // 시간 측정 끝
 			   	// result = (end - start);
    				//cout <<  "Execute time : " << (double)((result) / CLOCKS_PER_SEC) << endl; //결과 출력
				cout << "Total collision count : " << hash_table.get_collision_cnt() << endl;
				cout << "Load factor : " << hash_table.get_lf() << endl;
				}break;
			
			case(2):
				cout << "get test start.."  << endl;
				cout << "key : ";
				cin >> key;
				cout << hash_table.get(key) << endl;
				break;
			case(3):
				cout << "remove test start.."  << endl;
				cout << "key : ";
				cin >> key;
				cout << hash_table.remove(key) << endl;
				break;
			case(4):
				cout << "replace test start.."  << endl;
				break;
			case(5):
				cout << "size test start.."  << endl;
				cout << hash_table.size() << endl;
				break;
			case(6):
				cout << "isEmpty test start.."  << endl;
				cout << hash_table.isEmpty() << endl;
				break;
			case(7):
				cout << "containsKey test start.."  << endl;
				cout << "key : ";
				cin >> key;
				cout << hash_table.containsKey(key) << endl;
				break;
			case(8):
				cout << "containsValue test start.."  << endl;
				cout << "value : ";
				cin >> value;
				cout << hash_table.containsValue(value) << endl;
				break;
			case(9):
				cout << "hashCode test start.."  << endl;
				break;
			case(10):
				cout << "keySet test start.."  << endl;
				hash_table.keySet();
				break;
			case(11):
				cout << "values test start.."  << endl;
				hash_table.values();
				break;
			case(12):
				cout << "entrySet test start.."  << endl;
				hash_table.entrySet();
				break;
			case(13):
				cout << "rehashing test start.."  << endl;
				hash_table.rehashing();
				break;
			case(14):
				cout << "getOrDefault test start.."  << endl;
				cout << "key : ";
				cin >> key;
				cout << "default value : ";
				cin >> value;
				cout << hash_table.getOrDefault(key, value) << endl;
				break;
			case(15):
				cout << "putIfAbsent test start.."  << endl;
				cout << "key : ";
				cin >> key;
				cout << "value : ";
				cin >> value;
				hash_table.putIfAbsent(key, value);
				break;
			case(16):
				cout << "replace test start.." << endl;
				cout << "key : ";
				cin >> key;
				cout << "value : ";
				cin >> value;
				cout << hash_table.replace(key, value) << endl;
				break;
			case(17):
				cout << "print_vector_all start.." << endl;
				hash_table.print_vector_all();
				break;
			default:
				cout << "아직 추가되지 않은 번호입니다.." << endl;
				break;
		}
	}
	return 0;
}

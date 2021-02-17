# include <iostream>
# include <cstdio>
# include <vector>
# include <string>//문자열
# include <limits>//각 타입별 max값
# include <cmath>
# include <cassert>

using namespace std;
template<typename K, typename V>
class my_map{
    private:
		int table_size;
		int num = 0;
		vector<pair<K, V>>hash_table; //hash_table.first가 key, hash_table.second 가 value
		vector<pair<K, V>>entrys;
		int save_cnt = 0; // 적재 밀도를 구하기 위한 cnt
						  // put이 일어날 때마다 +1, remove가 일어날 때마다 -1
	public:
		// 생성자 선언
		my_map(K key, V value)
		{
			int key_value = trans_num(key);
			table_size = get_prime(key_value);
			int hash1_key = hash_key1(key, table_size);
			init_hash_table(hash1_key, key, value, table_size);
		};
		//////////////////////////////////////////////

		// 해싱함수(제산)
		int hash_key1(K key, int table_size)
		{
			int result = 0;
			int len = key.length();
			for (int i = 0; i < len; i++)
			{
				result += (int)key[i];
			}
			result = (result%table_size);
			return result;
		};

		// 충돌이 일어났을때 사용되는 해싱함수
		int hash_key2(K key, int table_size, int collision_num)
		{
			cout << "두번째 해시함수 시작.." << endl;
			int key_num = 0;
			int len = key.length();
			for (int i = 0; i < len; i++)
			{
				key_num = key_num + (int)key[i];
			}
			int hash1_key = (key_num%table_size);
			int hash2_key = 0;
			/// C-(k mod C) [C는 table_size보다 작은 소수]
			int C = get_prime(table_size);
			hash2_key = C - (key_num%C);
			hash2_key = (hash1_key + collision_num*hash2_key)%table_size;
			///
			return hash2_key;
		};

		void init_hash_table(int real_hash_key, K key ,V value, int table_size)
		{
			//엔트리 페어를 만들어야 하는가? 만들었음..
			pair<K, V> entrys_input = make_pair(key, value); 
			entrys.push_back(entrys_input);

			cout <<  endl;
			cout << "초기 테이블 사이즈는 " << table_size  << endl;
			cout << "초기 key 값은 " << entrys[0].first  << endl;
			cout << "초기 해시값은 " << real_hash_key  << endl;
			cout << "초기 value는 " << entrys[0].second  << endl;
			cout <<  endl;

			hash_table.resize(table_size);
			this->table_size = table_size;
			this->save_cnt++;

			hash_table[real_hash_key] = entrys[0];
		};

		// 아스키 코드로 바꿔서 더할 경우, are==era이기 때문에 다른 방법이 필요.
		int trans_num(K key)
		{
			int result = 0;
			int len = key.length();
			for (int i = 0; i < len; i++)
			{
				//result = 31*result + (int)key[i];
				result = result + (int)key[i];
			}
			// 이 경우 생각해줘야 함.
			//if(result < 0)
			//	cout << "오버플로우 일어남." << endl;
			return result;
		};

		// prime_num : return 0
		// 소수인지 확인한다.
		int check_prime(int table_size)
		{
			int count = 0;
			if(table_size == 1)
				return 1;
			for(int i = 2; i <= sqrt(table_size); i++)
			{
				if(!(table_size%i))
					count++;
				if(count>0)
					break;
			}
			return count;
		};

		int get_prime(int table_size)
		{
			int j = 1;
			int C = 0;
			cout << "소수 구하기 시작.." << endl;
			cout << "현재 테이블 사이즈는 " << table_size << endl;
			while(1)
			{
				if(check_prime(table_size-j)==0)
						{
								C = table_size-j;
								if(check_prime(table_size+j)==0)
										C=table_size+j;
								break;
						}
				j++;
			}
			cout << "소구 구하기 완료.." << C << endl;
			return C;
		};

		V put(K key, V value)
		{
			
			cout << "put function" << endl;
			bool flag = false;
			pair<K, V> is_input = make_pair(key, value);
			// 이놈이 다 말아먹는다//
			for(int i = 0; i < entrys.size(); i++)
			{
				if(entrys[i].first==key && entrys[i].second==value)
				{
					flag = true;
					break;
				}
			}
			if(flag == false){
				entrys.push_back(is_input);
			}
			////////////////////////
			int hash1_key = hash_key1(is_input.first, table_size);
			cout << "첫번째 해싱 결과는 " << hash1_key << endl;

			// 만약 첫 해싱 결과에서 충돌이 난다면,
			if(hash_table[hash1_key].first != "\0")
			{	
				// 충돌이 일어나지 않을때 까지 반복..
				while(1)
				{
					cout << "Collision 발생!!!" << endl;
					// 충돌 횟수 저장
					this->num++;
					cout << "충돌이 총 "<< num <<" 번 발생함." << endl;
					// 충돌 해결법 사용(이중해싱)
					int hash2_key = hash_key2(key, table_size, num);
					cout << "이중 해싱 결과 해시 값은 " << hash2_key << endl;
					// 동일한 키 값이 검색되는 경우, 값 교체
					// 동일한 키 값을 허용하지 않기 때문에
					if(hash_table[hash2_key].first == key)
					{
						cout << "키 값이 동일합니다.\nOld_value를 new_value로 교체합니다." << endl;
						hash_table[hash2_key].second = value;
						return "\0";
					}
					// 한번도 안쓰였고 비어있는 곳을 만나면, while 종료
					if(hash_table[hash2_key].first == "\0" && hash_table[hash2_key].second == "\0")
					{
						hash_table[hash2_key] = is_input;
						cout << hash2_key << "에 추가 완료!!" << endl;
						break;
					}
					// 이전에 삭제됐던 노드라면,
					if(hash_table[hash2_key].second == "delete_node")
					{
						bool flag = false;
						// entry scan
						// 동일한 key값이 존재하는지 확인
						for(int i = 0 ; i < entrys.size(); i++)
						{
							if(entrys[i].first == key)
								flag = true; // 있으면 true
								break;
						}
						// 없으면 해당 노드에 새로운 값으로 input
						if(flag == false)
						{
							hash_table[hash2_key] = is_input;
							cout << "지워졌던 노드이지만 중복키가 없기 때문에 추가 가능!!" << endl;
							cout << hash2_key << "에 추가 완료!!" << endl;
							break;
						}
					}
					// 테이블 끝까지 돌았으면 테이블 사이즈를 늘리고 Rehashing
					if((save_cnt+1 == table_size) || ((save_cnt+1)/table_size > 0.7))
					{
						cout << "현재 적재된 양은 " << save_cnt << endl;
						cout << "테이블 사이즈를 조정.. 아직 미구현..";
						rehashing();
						return "\0";
					}
					//cout << "너 탈출 못함 ㅋㅋ " << endl;
				}
			}
			else
			{
				// 그렇지 않다면, 해당 1번 해시 키 값에 key, value 추가.
				hash_table[hash1_key] = is_input;
				cout << hash1_key << "에 추가 완료!!" << endl;
			}
			// 충돌횟수 초기화
			this->num = 0;
			// 적재율 판단을 위한 카운트 증가
			this->save_cnt++;
			return "\0";
		};

		void rehashing(){
			hash_table.clear(); // 해시 테이블을 비우고,
			int re_table_size = get_prime(this->table_size*2);
			hash_table.resize(re_table_size); // 테이블 사이즈를 늘리고
			this->table_size = re_table_size;
			// 엔트리에 있는 항목들로 다시 재해싱..
			for(int i = 0; i < entrys.size(); i++)
			{
				put(entrys[i].first, entrys[i].second);
			}
			cout << endl;
			cout << "재해싱 종료.." << endl;
			cout << endl;
		}

		V remove(K key){
			// 엔트리도 지우고
			bool flag = false;
			for(int i = 0; i < entrys.size(); i++)
			{
				if(entrys[i].first == key)
				{
					entrys.erase(entrys.begin()+i);
					flag = true;
					break; // 중복되는 키값은 허용하지 않으므로 하나만 지우고 바로 빠져나온다.
				}
			}
			// 해시 테이블도 지우고
			// 지웠던 애라는 걸 알려주기까지 해야함.
			// second에 delete node라고 저장해두기
			if(flag==true){
				int hash1_key = hash_key1(key, table_size);
				// 1차 해시 값을 참조했을 때 같은 키값이 있으면
				if(hash_table[hash1_key].first==key)
				{
					string result = hash_table[hash1_key].second;
					hash_table[hash1_key]=make_pair("","delete_node");
					cout << "1차 해시 함수로 삭제 완료" << endl;
					return result;
				}
				else
				{
					while(1)
					{
						this->num++;
						int hash2_key = hash_key2(key, table_size, num);
						if(hash_table[hash2_key].first==key)
						{
							string result = hash_table[hash2_key].second;
							hash_table[hash2_key]=make_pair("","delete node");
							cout << "2차 해시 함수로 삭제 완료" << endl;
							return result;
							break;
						}
					}
				}
			}
			else
			{
				cout << "해당 키값이 현재 테이블에 포함되지 않습니다." << endl;
				return"\0";
			}
			this->save_cnt--;
			return"\0";
		}

		V get(K key){
			int hash1_key = hash_key1(key, table_size);
			if(hash_table[hash1_key].first==key){
				return hash_table[hash1_key].second;
			}
			while(1)
			{
				this->num++;
				cout << num << " 회 탐색 중.." << endl;
				// 탐색이 테이블 사이즈만큼 반복되면,
				// 모든 테이블을 탐색한 것.
				if(num==table_size)
				{
					cout << "없는 키 값입니다." << endl;
					break;
				}
				int hash2_key = hash_key2(key, table_size, num);
				if(hash_table[hash2_key].first==key)
				{
					return hash_table[hash2_key].second;
				}
				else
				{
					continue;
				}
			}
			return "\0";
		}

		void my_clear()
		{	
			cout << "clear function() start..." << endl;
			hash_table.clear();
			cout << hash_table.size() << endl;
			entrys.clear();
			cout << entrys.size() << endl;
			cout << "clear function() exit..." << endl;
			cout << endl;
		}

		int size()
		{
			cout << "size function() start..." << endl;
			cout << "size function() exit..." << endl;
			return hash_table.size();
		}

		vector<K> keySet()
		{
			vector<string> set;
			for(auto entry : entrys ) 
			{
				set.push_back(entry.first);
			}
			return set;
		}

		vector<V> values()
		{
			vector<string> set;
			for(auto entry : entrys ) 
			{
				set.push_back(entry.second);
			}
			return set;
		}

		vector<pair<K, V>> entrySet()
		{
			return entrys;
		}

		bool isEmpty()
		{
			for (int i = 0; i < hash_table.size(); i++)
			{
				if(hash_table[i].first.empty() == false)
					return false;
			}
			return true;
		}

		bool containsKey(K key)
		{
			for (int i = 0; i < hash_table.size(); i++)
			{
				if(hash_table[i].first == key)
					return true;
			}
			return false;
		}

		bool containsValue(V value)
		{
			for (int i = 0; i < hash_table.size(); i++)
			{
				if(hash_table[i].second == value)
					return true;
			}
			return false;
		}

		V getOrDefault(K key, V defaultValue)
		{
			for (int i = 0; i < hash_table.size(); i++)
			{
				if(hash_table[i].first == key)
					return hash_table[i].second;
			}
			return defaultValue;
		}

		V putIfAbsent(K key, V value)
		{
			if(containsKey(key)==false)
			{
				put(key,value);
				cout << "put complete" << endl;
				return value;
			}
			else
			{
				return "\0";
			}
		}

		V replace(K key, V value){
		if (hash_table.containsKey(key)) 
		{
			return hash_table.put(key, value);
		} 
		else
			return "\0";
		}

		void print_vector_all()
		{
			int cnt = 0;
			cout << "해시 테이블안의 데이터를 모두 출력합니다." << endl;
			for(int i = 0; i < hash_table.size(); i++)
			{
				if(hash_table[i].first.empty()==false){
					cnt++;
					cout << "index : " << i << endl;
					cout << hash_table[i].first << endl;
					cout << hash_table[i].second << endl;
				}
			}
			cout << "total : " << cnt << endl;
			cout << endl;
		};

		//소멸자 선언
		~my_map()
		{
			cout << "my_map class finish!!"  << endl;
		};
};

/*
V get(K key);
*/
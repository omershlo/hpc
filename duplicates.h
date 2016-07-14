#ifndef __DUPLICATES_H__
#define __DUPLICATES__

using namespace std;

struct messageInStack{
	int stackIndex;
	messageID id;
	messageArray message;
	bool operator==(const messageInStack& second)const{
		for(int i = 10; i > -1; i--)
			if(message[i]^second.message[i])
			{
				return false;
			}
		return true;
	}
};

struct hash_messageArray{
  size_t operator()(const messageArray &y) const{
	  u32 hashResult = 0;
	  for(int i=0;i<11;i++)
		  hashResult ^= hash<u32>()(y[i]) + 0x9e3779b9 + (hashResult<<6) + (hashResult>>2);
	  return hashResult;
  }
};

//
//struct hash_messageInStack{
//  size_t operator()(const messageInStack &y) const{
//	  u32 hashResult = 0;
//	  for(int i=0;i<11;i++)
//		  hashResult ^= hash<u32>()(y.message[i]) + 0x9e3779b9 + (hashResult<<6) + (hashResult>>2);
//	  return hashResult;
//  }
//};

struct Key{
	messageArray a;
	bool operator==(const Key& second)const{
		for(int i = 10; i > -1; i--)
			if(a[i]^second.a[i])
			{
				return false;
			}
		return true;
	}
};

struct hash_Key{
  size_t operator()(const Key &y) const{
	  u32 hashResult = 0;
	  for(int i=0;i<11;i++)
		  hashResult ^= hash<u32>()(y.a[i]) + 0x9e3779b9 + (hashResult<<6) + (hashResult>>2);
	  return hashResult;
  }
};


typedef	unordered_map<messageArray, messageID, hash_messageArray> messageHashTable;

#endif /*__DUPLICATES__*/

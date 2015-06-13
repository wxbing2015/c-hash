# summary #
Chash is a hash implement for c programing language.
It supply the basic hash data structure and the basic hash operation like create a hashtable, add\find\del a <k,v> element by k.
Besides you can access the <k,v> using the in the elements insertion order.

Cool, isn't it? And this is just the begining.
# How to Use it #
  * ## checkout it from the svn reposite ##
```
svn checkout http://c-hash.googlecode.com/svn/trunk/ c-hash
```
  * ## source files ##
> There are two sub dirs in c-hash dir.
> The implement of the hashtable is in sub dir "c-hash/util", and you can find the test code in sub dir "c-hash/src".

  * ## compile and try test ##
> Just type the commands as follows:
```
cd c-hash/src
make
./main
```

  * ## some typical codes here ##
> key types support : int | long | char`*`

> value types support : char | short | int | long | float | double | char`*`
```
//key:int, value:int
HashTable * ht = create_hashtable(10,int,int);
hash_add(ht,10,20);
hash_add(ht,20,30);
int value = 0;
hash_find(ht,10,&value);
printf("find value :[%d] of key [%d]", value,10);
```
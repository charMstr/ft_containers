## class rb_tree:

**This container is used as a base class for the containers:**

- **map**		(insert() is using insert\_unique())
- **multimap**  (insert() is using insert\_unique())
- **set**		(insert() is using insert\_equal())
- **multiset**	(insert() is using insert\_equal())

## prototype:
	
class rb\_tree: ````template \< class Key, class Value, class KeyOfValue, class Compare, class Alloc = std::allocator\<Value\> \> class rb\_tree;````

## template parameters explained:

### Key:
It is the Key of the container, used to sort items inserted in it. In the case
of maps and multimaps, it is the Key of a key-value pair.

### Value:
In the case of map and multimap, it it the std::pair\<key\_type, mapped\_type\>
In the case of set and multiset, it is not really used, it is the exact same as
the first parameter.

### KeyOfValue:
The third template parameter KeyOfValue, is present so that we can extract the
key out of the key-value pair, especially in the case of map and multimap and
the function object **ft::Select1st<key, value> --> key**.
In the case of set and multiset, the extraction of the key is done through the
use of the function object **ft::identity<type> --> type**.

_reference used for inspiration: https://www.programmersought.com/article/3619788121/ _

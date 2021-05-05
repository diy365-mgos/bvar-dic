# bVariant Dictionary Library
## Overview
This Mongoose OS library allows you to create and manipulate dictionaries adding or removing keys, easily, like you do in javascript. It extends the [bVariant library](https://github.com/diy365-mgos/bvar).
## Features
- **Dynamic size** - You can add or remove keys with no limits.
- **Dynamic data-type keys** - Key values haven't data type declared explicitly, but any of supported by [bVariant library](https://github.com/diy365-mgos/bvar).
- **Nested keys** - A dictionary's key value can be a dictionary, recursively, with no depth limits. 
- **JSON support** - You can dynamically create a dictionary from a JSON string or you can save it as JSON in a very easy way. Just include the [bVariant JSON library](https://github.com/diy365-mgos/bvar-json) into your project. 

## Get Started
Include the library into your `mos.yml` file.
```yaml
libs:
  - origin: https://github.com/diy365-mgos/bvar-dic
```
**C/C++ sample code**

Create an empty dictionary explicitly.
```c
#include "mgos_bvar_dic.h"

mgos_bvar_t dic = mgos_bvar_new_dic();
```
Otherwise, create a dictionary implicitly just adding one key to a *bVariant*.
```c
#include "mgos_bvar_dic.h"

// Example #1 - Dictionary from a type-less(NULL) bVariant
mgos_bvar_t dic = mgos_bvar_new();
mgos_bvar_add_key(dic, "Name", mgos_bvar_new_str("Mark"));

// Example #2 - Dictionary from an integer bVariant 
mgos_bvar_t dic = mgos_bvar_new_integer(10);
mgos_bvar_add_key(dic, "Name", mgos_bvar_new_str("Mark"));
```
## C/C++ APIs Reference
### Inherited APIs
A dictionary inherits following APIs defined in [bVariant library](https://github.com/diy365-mgos/bvar).
- [mgos_bvar_get_type()](https://github.com/diy365-mgos/bvar#mgos_bvar_get_type)
- [mgos_bvar_set_null()](https://github.com/diy365-mgos/bvar#mgos_bvar_set_null)
- [mgos_bvar_cmp()](https://github.com/diy365-mgos/bvar#mgos_bvar_cmp)
- [mgos_bvar_is_null()](https://github.com/diy365-mgos/bvar#mgos_bvar_is_null)
- [mgos_bvar_copy()](https://github.com/diy365-mgos/bvar#mgos_bvar_copy)
- [mgos_bvar_length()](https://github.com/diy365-mgos/bvar#mgos_bvar_length)
- [mgos_bvar_set_unchanged()](https://github.com/diy365-mgos/bvar#mgos_bvar_set_unchanged)
- [mgos_bvar_is_changed()](https://github.com/diy365-mgos/bvar#mgos_bvar_is_changed)
- [mgos_bvar_free()](https://github.com/diy365-mgos/bvar#mgos_bvar_free)

In addition, there are dictionary-designed functions.
### mgos_bvar_new_dic
```c
mgos_bvar_t mgos_bvar_new_dic();
```
Creates an empty dictionary. Returns `NULL` if error. The returned dictionary must be deallocated using `mgos_bvar_free()` (more details [here](https://github.com/diy365-mgos/bvar#mgos_bvar_free)).
### mgos_bvar_is_dic
```c
bool mgos_bvar_is_dic(mgos_bvarc_t var);
```
Returns `true` if the *bVariant* is a dictionary, or `false` otherwise.

|Parameter||
|--|--|
|var|A *bVariant*.|
### mgos_bvar_remove_keys
```c
void mgos_bvar_remove_keys(mgos_bvar_t dic);
```
Removes all keys from the dictionary. Removed keys are also automatically deallocated.

|Parameter||
|--|--|
|dic|A dictionary.|
### mgos_bvar_remove_key
```c
void mgos_bvar_remove_key(mgos_bvar_t dic, const char *key_name);
```
Removes the specified key from the dictionary. Removed key is also automatically deallocated.

|Parameter||
|--|--|
|dic|A dictionary.|
|key_name|The name of the key to remove.|
### mgos_bvar_has_key
```c
bool mgos_bvar_has_key(mgos_bvarc_t dic, const char *key_name);
```
Returns `true` if the dictionary contains the key, or `false` otherwise.

|Parameter||
|--|--|
|dic|A dictionary.|
|key_name|The key name.|
### mgos_bvar_get_keys
```c
mgos_bvar_enum_t mgos_bvar_get_keys(mgos_bvar_t dic);
```
Returns the keys enumerator of a dictionary, or `NULL` if error. The enumerator can be used with `mgos_bvar_get_next_key()`.

|Parameter||
|--|--|
|dic|A dictionary.|
### mgos_bvar_get_next_key
```c
bool mgos_bvar_get_next_key(mgos_bvar_enum_t *keys_enum, mgos_bvar_t *key_value, const char **key_name);
```
Gets the next key value iterating dictionary keys. Returns `false` if the end of the enumerator is reached, or `true` otherwise.

|Parameter||
|--|--|
|keys_enum|A reference to a keys enumerator returned by `mgos_bvar_get_keys()`.|
|key_value|The output key value. Optional, if `NULL` no key value is returned as output.|
|key_name|The output key name. Optional, if `NULL` no key name is returned as output.|
```c
// Example - Iterating dictionary keys
mgos_bvar_t key_value;
const char *key_name;
mgos_bvar_enum_t keys_enum = mgos_bvar_get_keys(dic);
while (mgos_bvar_get_next_key(&keys_enum, &key_value, &key_name)) {
  printf("Key '%s' of type %d found in dictionary.", key_name, mgos_bvar_get_type(key_value));
}
```
### mgos_bvarc_get_keys
```c
mgos_bvarc_enum_t mgos_bvarc_get_keys(mgos_bvarc_t dic);
```
Returns the keys enumerator of a readonly dictionary, or `NULL` if error. The enumerator can be used with `mgos_bvarc_get_next_key()`.

|Parameter||
|--|--|
|dic|A readonly dictionary.|
### mgos_bvarc_get_next_key
```c
bool mgos_bvarc_get_next_key(mgos_bvarc_enum_t *keys_enum, mgos_bvarc_t *key_value, const char **key_name);
```
Gets the next key value iterating readonly dictionary keys. Returns `false` if the end of the enumerator is reached, or `true` otherwise. The retrieved key value is readonly.

|Parameter||
|--|--|
|keys_enum|A reference to a readonly keys enumerator returned by `mgos_bvarc_get_keys()`.|
|key_value|The output readonly key value. Optional, if `NULL` no key value is returned as output.|
|key_name|The output key name. Optional, if `NULL` no key name is returned as output.|
```c
// Example - Iterating readonly dictionary keys
mgos_bvarc_t key_value;
const char *key_name;
mgos_bvarc_enum_t keys_enum = mgos_bvarc_get_keys(var);
while (mgos_bvarc_get_next_key(&keys_enum, &key_value, &key_name)) {
  printf("Key '%s' of type %d found in dictionary.", key_name, mgos_bvar_get_type(key_value));
}
```
### mgos_bvar_get_key
```c
mgos_bvar_t mgos_bvar_get_key(mgos_bvar_t dir, const char *key_name);;
```
Returns the key value of a dictionary, or `NULL` if the key doesn't exist.

|Parameter||
|--|--|
|dic|A dictionary.|
|key_name|The name of the key to return.|
### mgos_bvarc_get_key
```c
mgos_bvarc_t mgos_bvarc_get_key(mgos_bvarc_t dic, const char *key_name);
```
Returns the key value of a readonly dictionary, or `NULL` if the key doesn't exist. The returned value is readonly.

|Parameter||
|--|--|
|dic|A dictionary.|
|key_name|The name of the key to return.|
### mgos_bvar_try_get_key
```c
bool mgos_bvar_try_get_key(mgos_bvar_t dic, const char *key_name, mgos_bvar_t *key_value);
```
Try to get the key value of a dictionary. Returns `true` if the key exists, or `false` otherwise.

|Parameter||
|--|--|
|dic|A dictionary.|
|key_name|The output key name. Optional, if `NULL` no key name is returned.|
|key_value|The output key value. Optional, if `NULL` no key value is returned.|
### mgos_bvarc_try_get_key
```c
bool mgos_bvarc_try_get_key(mgos_bvarc_t dic, const char *key_name, mgos_bvarc_t *key_value);
```
Try to get the key value of a readonly dictionary. Returns `true` if the key exists, or `false` otherwise. The retrieved key value is readonly.

|Parameter||
|--|--|
|dic|A dictionary.|
|key_name|The output key name. Optional, if `NULL` no key name is returned as output.|
|key_value|The output readonly key value. Optional, if `NULL` no key value is returned as output.|
### mgos_bvar_add_key
```c
bool mgos_bvar_add_key(mgos_bvar_t dic, const char *key_name, mgos_bvar_t key_value);
```
Adds the key to a dictionary. Returns `true` if successfully added, or `false` otherwise.

|Parameter||
|--|--|
|dic|A dictionary.|
|key_name|The name of the key to add.|
|key_value|The key value.|
### mgos_bvar_merge
```c
bool mgos_bvar_merge(mgos_bvarc_t src_var, mgos_bvar_t dest_var);
```
Merges a source dictionary into the destination one. Returns `true` if merged successfully, or `false` otherwise. If the source *bVariant* is not a dictionary it is just copied into the destination *bVariant*, like `mgos_bvar_copy()` does. (more details [here](https://github.com/diy365-mgos/bvar#mgos_bvar_copy)). 

|Parameter||
|--|--|
|src_var|A source *bVariant*.|
|dest_var|A destination *bVariant*.|
## To Do
- Implement javascript APIs for [Mongoose OS MJS](https://github.com/mongoose-os-libs/mjs).

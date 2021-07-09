# bVariantDictionaries Library
## Overview
This Mongoose OS library allows you to create and manipulate bVariantDictionaries adding or removing keys, easily, like you do in javascript. It extends the [bVariant library](https://github.com/diy365-mgos/bvar).
## Features
- **Dynamic size** - You can add or remove keys with no limits.
- **Optimized memory allocation** - The library inherits the [bVariant library](https://github.com/diy365-mgos/bvar) optimized memory allocation. In addition, blocks of 8 dictionary's items are automatically allocated and disposed to prevent memory fragmentation.
- **Dynamic data-type keys** - Key values haven't data type declared explicitly, but any of supported by [bVariant library](https://github.com/diy365-mgos/bvar).
- **Nested keys** - A dictionary's key value can be a dictionary, recursively, with no depth limits. 
- **JSON support** - You can dynamically create a dictionary from a JSON string or you can save it as JSON in a very easy way. Just include the [bVariant JSON library](https://github.com/diy365-mgos/bvar-json) in your project. 

## Get Started in C/C++
Include the library in your `mos.yml` file.
```yaml
libs:
  - origin: https://github.com/diy365-mgos/bvar-dic
```
#### Example 1 - Create an empty bVariantDictionary explicitly
```c
#include "mgos_bvar_dic.h"

mgos_bvar_t dic = mgos_bvar_new_dic();
```
#### Example 2 - Create a bVariantDictionary implicitly
```c
#include "mgos_bvar_dic.h"

// Example #1 - bVariantDictionary from a type-less(NULL) bVariant
mgos_bvar_t dic = mgos_bvar_new();
mgos_bvar_add_key(dic, "Name", mgos_bvar_new_str("Mark"));

// Example #2 - bVariantDictionary from an integer bVariant 
mgos_bvar_t dic = mgos_bvar_new_integer(10);
mgos_bvar_add_key(dic, "Name", mgos_bvar_new_str("Mark"));
```
## C/C++ APIs Reference
### Inherited bVariant APIs
A bVariantDictionary inherits following [bVariant](https://github.com/diy365-mgos/bvar) APIs:
- [mgos_bvar_get_type()](https://github.com/diy365-mgos/bvar#mgos_bvar_get_type)
- [mgos_bvar_set_null()](https://github.com/diy365-mgos/bvar#mgos_bvar_set_null)
- [mgos_bvar_is_null()](https://github.com/diy365-mgos/bvar#mgos_bvar_is_null)
- [mgos_bvar_cmp()](https://github.com/diy365-mgos/bvar#mgos_bvar_cmp)
- [mgos_bvar_copy()](https://github.com/diy365-mgos/bvar#mgos_bvar_copy)
- [mgos_bvar_merge()](https://github.com/diy365-mgos/bvar#mgos_bvar_merge)
- [mgos_bvar_length()](https://github.com/diy365-mgos/bvar#mgos_bvar_length)
- [mgos_bvar_set_unchanged()](https://github.com/diy365-mgos/bvar#mgos_bvar_set_unchanged)
- [mgos_bvar_is_changed()](https://github.com/diy365-mgos/bvar#mgos_bvar_is_changed)
- [mgos_bvar_clear()](https://github.com/diy365-mgos/bvar#mgos_bvar_clear)
- [mgos_bvar_free()](https://github.com/diy365-mgos/bvar#mgos_bvar_free)

In addition, there are the following dictionary-designed APIs.
### mgos_bvar_new_dic
```c
mgos_bvar_t mgos_bvar_new_dic();
```
Creates an empty bVariantDictionary. Returns `NULL` if error. The returned dictionary must be deallocated using [mgos_bvar_free()](https://github.com/diy365-mgos/bvar#mgos_bvar_free).
### mgos_bvar_is_dic
```c
bool mgos_bvar_is_dic(mgos_bvarc_t var);
```
Returns `true` if the bVariant is a bVariantDictionary, or `false` otherwise.

|Parameter||
|--|--|
|var|A bVariant.|
### mgos_bvar_remove_keys
```c
void mgos_bvar_remove_keys(mgos_bvar_t dic);
```
Removes all keys without disposing them. If you want to dispose keys as well, use [mgos_bvar_clear()](https://github.com/diy365-mgos/bvar#mgos_bvar_clear) instead.

|Parameter||
|--|--|
|dic|A bVariantDictionary.|
### mgos_bvar_remove_key
```c
mgos_bvar_t mgos_bvar_remove_key(mgos_bvar_t dic, const char *key_name);
```
Removes the specified key without disposing it. If you want to dispose the key as well, use `mgos_bvar_delete_key()` instead. Returns the removed bVariant or `NULL` if the dictionary hasn't that key.

|Parameter||
|--|--|
|dic|A bVariantDictionary.|
|key_name|The name of the key to remove.|
### mgos_bvar_delete_key
```c
void mgos_bvar_remove_key(mgos_bvar_t dic, const char *key_name);
```
Removes and disposes the specified key. If you do not want to dispose the key, use `mgos_bvar_remove_key()` instead.

|Parameter||
|--|--|
|dic|A bVariantDictionary.|
|key_name|The name of the key to remove and dispose.|
### mgos_bvar_has_key
```c
bool mgos_bvar_has_key(mgos_bvarc_t dic, const char *key_name);
```
Returns `true` if the bVariantDictionary contains the key, or `false` otherwise.

|Parameter||
|--|--|
|dic|A bVariantDictionary.|
|key_name|The key name.|
### mgos_bvar_get_keys
```c
mgos_bvar_enum_t mgos_bvar_get_keys(mgos_bvar_t dic);
```
Returns the keys enumerator of a bVariantDictionary, or `NULL` if error. The enumerator can be used with `mgos_bvar_get_next_key()`.

|Parameter||
|--|--|
|dic|A bVariantDictionary.|
### mgos_bvar_get_next_key
```c
bool mgos_bvar_get_next_key(mgos_bvar_enum_t *keys_enum, mgos_bvar_t *key_value, const char **key_name);
```
Gets the next key value iterating bVariantDictionary keys. Returns `false` if the end of the enumerator is reached, or `true` otherwise.

|Parameter||
|--|--|
|keys_enum|A reference to a keys enumerator returned by `mgos_bvar_get_keys()`.|
|key_value|The output key value. Optional, if `NULL` no key value is returned as output.|
|key_name|The output key name. Optional, if `NULL` no key name is returned as output.|

Example - Iterating bVariantDictionary keys:
```c
mgos_bvar_t key_value;
const char *key_name;
mgos_bvar_enum_t keys_enum = mgos_bvar_get_keys(dic);
while (mgos_bvar_get_next_key(&keys_enum, &key_value, &key_name)) {
  printf("Key '%s' of type %d found in bVariantDictionary.", key_name, mgos_bvar_get_type(key_value));
}
```
### mgos_bvarc_get_keys
```c
mgos_bvarc_enum_t mgos_bvarc_get_keys(mgos_bvarc_t dic);
```
Returns the keys enumerator of a readonly bVariantDictionary, or `NULL` if error. The enumerator can be used with `mgos_bvarc_get_next_key()`.

|Parameter||
|--|--|
|dic|A readonly bVariantDictionary.|
### mgos_bvarc_get_next_key
```c
bool mgos_bvarc_get_next_key(mgos_bvarc_enum_t *keys_enum, mgos_bvarc_t *key_value, const char **key_name);
```
Gets the next key value iterating readonly bVariantDictionary keys. Returns `false` if the end of the enumerator is reached, or `true` otherwise. The retrieved key value is readonly.

|Parameter||
|--|--|
|keys_enum|A reference to a readonly keys enumerator returned by `mgos_bvarc_get_keys()`.|
|key_value|The output readonly key value. Optional, if `NULL` no key value is returned as output.|
|key_name|The output key name. Optional, if `NULL` no key name is returned as output.|

Example - Iterating readonly bVariantDictionary keys:
```c
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
Returns the key value of a bVariantDictionary, or `NULL` if the key doesn't exist.

|Parameter||
|--|--|
|dic|A bVariantDictionary.|
|key_name|The name of the key to return.|
### mgos_bvarc_get_key
```c
mgos_bvarc_t mgos_bvarc_get_key(mgos_bvarc_t dic, const char *key_name);
```
Returns the key value of a readonly bVariantDictionary, or `NULL` if the key doesn't exist. The returned value is readonly.

|Parameter||
|--|--|
|dic|A bVariantDictionary.|
|key_name|The name of the key to return.|
### mgos_bvar_try_get_key
```c
bool mgos_bvar_try_get_key(mgos_bvar_t dic, const char *key_name, mgos_bvar_t *key_value);
```
Try to get the key value of a bVariantDictionary. Returns `true` if the key exists, or `false` otherwise.

|Parameter||
|--|--|
|dic|A bVariantDictionary.|
|key_name|The output key name. Optional, if `NULL` no key name is returned.|
|key_value|The output key value. Optional, if `NULL` no key value is returned.|
### mgos_bvarc_try_get_key
```c
bool mgos_bvarc_try_get_key(mgos_bvarc_t dic, const char *key_name, mgos_bvarc_t *key_value);
```
Try to get the key value of a readonly bVariantDictionary. Returns `true` if the key exists, or `false` otherwise. The retrieved key value is readonly.

|Parameter||
|--|--|
|dic|A bVariantDictionary.|
|key_name|The output key name. Optional, if `NULL` no key name is returned as output.|
|key_value|The output readonly key value. Optional, if `NULL` no key value is returned as output.|
### mgos_bvar_add_key
```c
bool mgos_bvar_add_key(mgos_bvar_t dic, const char *key_name, mgos_bvar_t key_value);
```
Adds the key to a bVariantDictionary. Returns `true` if successfully added, or `false` otherwise.

|Parameter||
|--|--|
|dic|A bVariantDictionary.|
|key_name|The name of the key to add.|
|key_value|The key value.|
## To Do
- Implement javascript APIs for [Mongoose OS MJS](https://github.com/mongoose-os-libs/mjs).

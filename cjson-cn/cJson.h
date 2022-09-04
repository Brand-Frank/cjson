//#pragma once

#ifndef _CJSON_H_
#define _CJSON_H_

/**
两个板块：
json解析、节点的增删改查

{
	"name": "Jack (\"Bee\") Nimble",
	"format": {
		"type":       "rect",
		"width":      1920,
		"height":     1080,
		"interlace":  false,
		"frame rate": 24
	}
}
0
逻0辑0上的树状结构

root ---> child(name)
				format--->child(type)
								width
								height
								interlace
								frame rate
*/

#define cJSON_False		0
#define cJSON_True		1
#define cJSON_NULL		2
#define cJSON_Number	3
#define cJSON_String	4
#define cJSON_Array		5
#define cJSON_Object	6


/**创建一个string值为name的cJSON_False节点，并添加到object
*/
#define cJSON_AddFalseToObject(object, name) \
	cJSON_AddItemToObject(object, name, cJSON_CreateFalse())

/**创建一个string值为name的cJSON_True节点,并添加到object节点*/
#define cJSON_AddTrueToObject(object,name) \
	cJSON_AddItemToObject(object, name, cJSON_CreateTrue())

/**创建一个string值为name的cJSON_Bool/False节点,并添加到object节点*/
#define cJSON_AddBoolToObject(object,name, b) \
	cJSON_AddItemToObject(object, name, cJSON_CreateBool(b))

/**创建一个string值为name的cJSON_NULL节点,并添加到object节点*/
#define cJSON_AddNULLToObject(object,name) \
	cJSON_AddItemToObject(object, name, cJSON_CreateNull())

/**创建一个string值为name的cJSON_Number节点,并添加到object节点*/
#define cJSON_AddNumberToObject(object,name, number) \
	cJSON_AddItemToObject(object, name, cJSON_CreateNumber(number))

/**创建一个string值为name的cJSON_String节点,并添加到object节点*/
#define cJSON_AddStringToObject(object,name, s) \
	cJSON_AddItemToObject(object, name, cJSON_CreateString(s))

#define cJSON_SetIntValue(object, val)\
	((object)?((object)->valueInt=(object)->valueDouble=(val)):(val))

#define cJSON_SetNumberValue(object, val)\
	((object)?((object)->valueInt=(object)->valueDouble=(val)):(val))

typedef struct cJSON
{
	struct cJSON *next, *prev;
	struct cJSON *child;

	/**array以及object类型需要设立子节点*/
	int type;

	char *valueString;
	int valueInt;
	double valueDouble;

	char *string;
}cJSON;

/**常用解析函数*/

/**
 *@brief	解析json数据，将数据填入json树中
 *@param	value (const char *):char*指针，指向待解析的json数据
 *@return	json树的根节点
*/
cJSON *cJSON_Parse(const char *value);

/**
 *@brief	从item节点开始递归遍历，将节点树转换为字符串
 *@param	item(cJSON *item):cJson节点
 *@return	字符串指针，从item节点解析后的树字符串
 *@note		使用该函数后，需要根据返回的char*指针释放内存。
	out = cJSON_Print(cJSON *item)
	printf("%s",out);
	free(out)
*/
char *cJSON_Print(cJSON *item);

/**
 *@brief	从根节点开始递归删除json树各个及诶单，释放内存
 *@param	c(cJson *c):cJSON节点
 *@return	void
*/
void cJSON_Delete(cJSON *c);

/**
 *@brief	创建一个cJSON节点，并设置节点类型为cJSON_Object
 *@param	void
 *@return	cJson_Object 类型的节点指针。
*/
cJSON *cJSON_CreateObject(void);

/**
 *@brief	创建一个cJSON节点，并设置节点类型为cJSON_String
 *@param	string(char *string)
 *@return	cJSON_String 类型的节点指针
*/
cJSON *cJSON_CreateString(const char *string);

/**
 *@brief	创建一个cJSON节点，并设置节点类型为cJSON_Number
 *@param	num(double)
 *@return	cJSON_Number 类型的节点指针
*/
cJSON *cJSON_CreateNumber(double num);

/**
 *@brief	创建一个cJSON节点，并设置节点类型为cJSON_Array
 *@param	void
 *@return	cJSON_Array 类型的节点指针
*/
cJSON *cJSON_CreateArray(void);

/**
 *@brief	创建一个cJSON节点，并设置节点类型为cJSON_Bool
 *@param	void
 *@return	cJson_Bool 类型的节点指针
*/
cJSON *cJSON_CreateBool(int b);

/**
 *@brief	创建一个cJSON节点，并设置节点类型为cJSON_True
 *@param	void
 *@return	cJSON_True 类型的节点指针
*/
cJSON *cJSON_CreateTrue(void);

/**
 *@brief	创建一个cJSON节点，并设置节点类型为cJSON_False
 *@param	void
 *@return	cJSON_False 类型的节点指针
*/
cJSON *cJSON_CreateFalse(void);

/**
 *@brief	创建一个cJSON节点，并设置节点类型为cJSON_Null
 *@param	void
 *@return	cJSON_Null 类型的节点指针
*/
cJSON *cJSON_CreateNull(void);


/***
 *@brief 将item节点名称设置为string，如果object节点没有子节点，就将item设置为object节点的子节点。
	否则将item添加到object->child链表尾部，成为object子节点的兄弟节点
 *@param	object(cJSON *):被添加节点
 *@param	string(char *)：要添加的节点的名称
 *@param	item(cJSON *)：要添加的节点
* @return	void
*/
void cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);

/**
 *@brief	将item添加到array节点
 *@param	array(cJSON *):被添加节点
 *@param	item(cJSON *)：要添加的节点
 *@return	void
*/
void cJSON_AddItemToArray(cJSON *array, cJSON *item);

/**
 * @brief 
 * 
 * @param value 
 * @param return_parse_end 
 * @param require_null_terminated 
 * @return cJSON* 
 */
cJSON *cJSON_ParseWithOpts(const char *value, const char **return_parse_end, int require_null_terminated);

cJSON *cJSON_New_Item();

/**
 * @brief 跳过一些字符
 * 
 * @param in 
 * @return const char* 
 */
const char *skip(const char *in);
char *cJSON_GetEndPosition(void);

/**
 * @brief 
 * 
 * @param item 
 * @param value 
 * @return const char* 
 */
const char *parse_value(cJSON *item, const char *value);

/**
 * @brief 
 * 
 * @param item 
 * @param str 
 * @return const char* 
 */
const char* parse_string(cJSON *item, const char *str);
const char* parse_number(cJSON *item, const char *num);
/**
 * @brief 
 * 
 * @param item 
 * @param value 
 * @return const char* 
 */
const char* parse_Array(cJSON *item, const char *value);
/**
 * @brief 
 * 
 * @param item 
 * @param value 
 * @return const char* 
 */
const char* parse_Object(cJSON *item, const char *value);

char *cJSON_strdup(const char *str);

/**
 * @brief 打印数字
 * 
 * @param item 
 * @return char* 
 */
char *print_number(cJSON *item);

/**
 * @brief 
 * 
 * @param item 
 * @param isName 
 * @return char* 
 */
char *print_string(cJSON *item);

//["OSCAR",123,XXX]
/**
 * @brief 
 * 
 * @param item 
 * @param depth 
 * @param fmt 
 * @return char* 
 */
char *print_array(cJSON *item, int depth, int fmt);

/**
 * @brief 
 * 
 * @param item 
 * @param depth 
 * @param fmt 
 * @return char* 
 */
char *print_object(cJSON *item, int depth, int fmt);

/**
 * @brief 
 * 
 * @param item 
 * @param depth 
 * @param fmt 
 * @return char* 
 */
char *print_value(cJSON *item,int depth, int fmt);

cJSON *cJSON_DetachItemFromArray(cJSON *array, int which);
void cJSON_DeleteItemFromArray(cJSON *array, int which);

int cJSON_strcasecmp(const char *s1, const char *s2); //strcmp()

cJSON *cJSON_DetachItemFromObject(cJSON *object, const char *string);
void cJSON_DeleteItemFromObject(cJSON *object, int which);

void cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newItem);

void cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newItem);
void cJSON_ReplaceItemInObject(cJSON *object, const char *string, cJSON *newItem);

#endif // !_CJSON_H_
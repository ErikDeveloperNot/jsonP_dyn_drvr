//#include "jsonP_parser.h"
//#include "jsonP_buffer_parser.h"
#include "jsonP_push_parser.h"
#include "net_chunk_impl.h"


#include <iostream>
#include <iomanip>
//#include <fstream>
#include <stdio.h>
#include <chrono>
#include <thread>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



typedef std::chrono::high_resolution_clock clock2;
typedef std::chrono::duration<float, std::milli> mil;

jsonP_json * create_json_doc();
char * parse_file(std::string, std::string &);

int main(int argc, char **argv)
{

//for (size_t ii=0; ii<1000; ii++) {
	//sample of creating json object and accessing its elements
	{
		std::cout << "\n\n**********************************************************\n";
		std::cout << "sample of creating json object and accessing its elements...\n";
		
		jsonP_json *json = nullptr;
		
		try {
			json = create_json_doc();
			char *pretty_json = json->stringify_pretty();
			std::cout << "json after creation:\n" << pretty_json << "\n";
			free(pretty_json);
			
			error err;
			search_path_element paths[3];
			char p3[] = {"O-new_obj_key-O-new_obj_key_embed-A-3"};
			char delim3[] = {"-"};

			if (json->build_search_path(p3, delim3, paths) != 0) {
				std::cout << "**** ERROR building search path *****" << std::endl;
			}

			std::cout << "\n ---- Deleting ---- \n";
	//		if (json->delete_value(paths, 3, NULL, &err) != 0) {
			if (json->delete_value("/new_obj_key/obj_key_embed/3", "/", &err) != 1) {
				std::cout << "**** ERROR deleting, error code: " << err << std::endl;
			} else {
				pretty_json = json->stringify_pretty();
				std::cout << "json after delete:\n" << pretty_json << "\n";
				free(pretty_json);
			}
			
			char p4[] = {"O-new_obj_key-O-new_obj_key_embed"};

			if (json->build_search_path(p4, "-", paths) != 0) {
				std::cout << "**** ERROR building search path *****" << std::endl;
			}
			\
			unsigned int member_cnt = json->get_members_count(paths, 2);
			std::cout << "\nmembers count: " << member_cnt << std::endl;
			std::cout << "members count: " << json->get_members_count("/new_obj_key/obj_key_embed", "/") << std::endl;

			//sample getting object keys using the object_id
			object_id test_id = json->get_object_id(paths, 1);
			struct object_key *obj_keys;
			unsigned int k_cnt = json->get_keys(test_id, obj_keys);
			std::cout << "\nNumber of Keys: " << k_cnt << std::endl;
			
			for (unsigned int i=0; i<k_cnt; i++) {
				std::cout << "type: " << obj_keys[i].type << ", key: " << ((obj_keys[i].type == empty) ? "n/a" : obj_keys[i].key) << std::endl;
			}

			free(obj_keys);

			//sample getting object keys using search_path_element
	//		k_cnt = json->get_keys(paths, 1, obj_keys);					//search_path_element
	//		char p_k[] = {"/new_obj_key"};									//char * path
	//		k_cnt = json->get_keys(p_k, delim, obj_keys);
	//		std::cout << "Number of Keys: " << k_cnt << std::endl;
	//
	//		for (unsigned int i=0; i<k_cnt; i++) {
	//			std::cout << "type: " << obj_keys[i].type << ", key: " << obj_keys[i].key << std::endl;
	//		}
	//
	//		free(obj_keys);

			//print contents of array using get_next_array_element. the first call takes an object_id or search_path_element
			// each call after takes 0 instead of the object_id. An empty element_type is returned when no more elements
			char p5[] = {"O-string_array\0"};
	//		char p_a[] = {"/string_array"};
			json->build_search_path(p5, delim3, paths);
			const void *v;

	//		element_type t_arry = json->get_next_array_element(paths, 1, v);
			element_type t_arry = json->get_next_array_element("/string_arry_key", "/", v);
			std::cout << "\nType returned: " << get_element_type_string(t_arry) << std::endl;
			std::cout << "Value returned: " << (char*)v << std::endl;
			t_arry = json->get_next_array_element(0, v);
			std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
			std::cout << "Value returned: " << std::endl;
			t_arry = json->get_next_array_element(0, v);
			std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
			std::cout << "Value returned: " << *(const long*)v << std::endl;
			t_arry = json->get_next_array_element(0, v);
			std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
			std::cout << "Value returned: " << *(double*)v << std::endl;
			t_arry = json->get_next_array_element(0, v);
			std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
			t_arry = json->get_next_array_element(0, v);
			std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
			t_arry = json->get_next_array_element(0, v);
			std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
			std::cout << "Element count: " << json->get_elements_count(*(object_id*)v) << std::endl;
			t_arry = json->get_next_array_element(0, v);
			std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
			std::cout << "Element count: " << json->get_members_count(*(object_id*)v) << std::endl;
			t_arry = json->get_next_array_element(0, v);
			std::cout << "Type returned: " << get_element_type_string(t_arry) << std::endl;
			
			//get simple value types
			std::cout << "\ndouble value: " << json->get_double_value("/new_obj_key/double_key", "/", &err) << std::endl; 
			std::cout << "long value: " << json->get_long_value("/new_obj_key/long_key", "/", &err) << std::endl;
			std::cout << "bool value: " << json->get_bool_value("/new_obj_key/bool_t_key", "/", &err) << std::endl; 
			std::cout << "string value: " << json->get_string_value("/new_obj_key/NEW_KEY", "/", &err) << std::endl; 
			
			//update value
			char string_v[] = {"new string value\0"};
	//		char path_to_update[] = {"/new_obj_key/NEW_KEY"};
	//		json->update_value(paths, 2, string, string_v);
			json->update_value("/new_obj_key/NEW_KEY", "/", string, string_v);
			std::cout << "updated string value: " << json->get_string_value("/new_obj_key/NEW_KEY", "/", &err) << std::endl; 
			
			object_id array_mem_id = json->get_object_id("/string_arry_key/2", "/");
			std::cout << "/string_arry_key/2 element type: " << json->get_elements_type(array_mem_id) << std::endl;
			std::cout << "Get array index 2 using object_id, long value: " << json->get_long_value(array_mem_id, array_indx, &err) << std::endl;
			std::cout << "Get array index 2 using path, long value: " << json->get_long_value("/string_arry_key/2", "/", &err) << std::endl;
			
//			search_path_element p[2];
//			p[0].type = object_key;
//			p[0].key = "string_arry_key";
//			p[1].type = array_indx;
//			p[1].key = "2";
//			std::cout << "Get array index 2 using SEARCH path, long value: " << json->get_long_value(p, 2, &err) << std::endl;
						
			std::cout << "\n\n";
						
			delete json;
		} catch (jsonP_exception &ex) {
			std::cout << "json exception caught: " << ex.what() << std::endl;
			delete json;
		}
	}
	
	
	//sample parsing json text files
	std::cout << "\n\n**********************************************************\n";
	std::cout << "sample parsing json file using the nonbuffer parser, the whole file is loaded into memory first...\n";
	jsonP_json *parse_doc = nullptr;
	jsonP_parser *parser =  nullptr;

	try {
		std::cout << "\n*** opening text file ***\n";
		std::string json;
//		char *json2 = parse_file("/Users/user1/Downloads/large.json", json);
//		char *json2 = parse_file("../samples/webapp.json", json);
		char *json2 = parse_file("../samples/sample1.json.small", json);
//		char *json2 = parse_file("/Users/user1/Git/rapidjson/bin/encodings/utf8.json", json);
//		char *json2 = parse_file("/Users/user1/Git/rapidjson/bin/data/sample", json);
		std::cout << "*** parsing text file with jsonP ***\n" << std::endl;

		auto t0 = clock2::now();
		parser = new jsonP_parser{json2, (unsigned int)strlen(json2)}; //, DONT_SORT_KEYS}; // | CONVERT_NUMERICS };
		parse_doc = parser->parse();
		auto t1 = clock2::now();

		std::cout << "\nDONE parsing, elapsed time: " << mil(t1-t0).count() << "ms\n" << std::endl;
		parse_stats stats = parser->get_parse_stats();
		std::cout << "Parse stats, data increases: " << stats.data_increases << ", stack buffer increases: " << stats.stack_buf_increases << std::endl;

		t0 = clock2::now();
		char *stringify = parse_doc->stringify();		
		t1 = clock2::now();
		std::cout << "\nDONE stringify, elapsed time: " << mil(t1-t0).count() << "ms\n" << std::endl;
		std::cout << stringify << std::endl;
		free(stringify);

		t0 = clock2::now();
		char *stringify_pretty = parse_doc->stringify_pretty(10);	
		t1 = clock2::now();
		std::cout << "\nDONE stringify_pretty, elapsed time: " << mil(t1-t0).count() << "ms\n" << std::endl;
		std::cout << stringify_pretty << std::endl;
		free(stringify_pretty);

		std::cout << "After adding a new element to the parsed json\n";
		object_id id_ = parse_doc->get_doc_root();
		char key_[] = {"This_is_the_new_key\0"};
		char val_[] = {"This is the new value added to a parsed document\0"};
		parse_doc->add_value_type(string, id_, key_, val_);
		stringify_pretty = parse_doc->stringify_pretty();
		std::cout << stringify_pretty << std::endl;
		free(stringify_pretty);
		
		error err = none;
		double d = parse_doc->get_double_value("float\0", id_, &err);
		std::cout << "double: " << d << ", err: " << err << std::endl;
		long l = parse_doc->get_long_value("int_long\0", id_, &err);
		std::cout << "long: " << l << ", err: " << err << std::endl;
		double dv = 872333.123;
		int success = parse_doc->update_value("/float", "/", numeric_double, &dv);
		std::cout << "success: " << success << std::endl;
		long lv = 82377542934;
		success = parse_doc->update_value("/int_long", "/", numeric_long, &lv);
		std::cout << "success: " << success << std::endl;
		char shrt_str[] = {"short string plus some"};
		success = parse_doc->update_value("/string", "/", string, shrt_str);
		std::cout << "success: " << success << std::endl;
		success = parse_doc->add_value_type(string, id_, "new string", shrt_str);
		std::cout << "success: " << success << std::endl;
		
		stringify_pretty = parse_doc->stringify_pretty();
		std::cout << stringify_pretty << std::endl;
		free(stringify_pretty);
		
		t0 = clock2::now();
		delete parse_doc;
		delete parser;
		t1 = clock2::now();
		std::cout << "\nfree elapsed time: " << mil(t1-t0).count() << "ms\n" << std::endl;
		
	} catch (jsonP_exception &ex) {
		std::cout << "Parse exception parsing text file: " << ex.what() << std::endl;
		std::cout << "Error snip:\n" << parser->get_error_snip(100, 100) << std::endl;
		delete parse_doc;
		delete parser;
	}


	// sample parsing json file using the buffer parser
	std::cout << "\n\n**********************************************************\n";
	std::cout << "sample parsing json file using the buffer parser...\n";
	jsonP_buffer_parser *buf_parser = nullptr;
	jsonP_json *doc_buf = nullptr;
	
	try {
	//	buf_parser = new jsonP_buffer_parser{"/Users/user1/Downloads/large.json", 8192};
		buf_parser = new jsonP_buffer_parser{"../samples/webapp.json", 1000};

		auto buf_t0 = clock2::now();
		doc_buf = buf_parser->parse();
		auto buf_t1 = clock2::now();
		std::cout << "buffer parser parse time: " << mil(buf_t1-buf_t0).count() << "/ms" << std::endl;

		buf_t0 = clock2::now();
		char *stringify_pretty_buf = doc_buf->stringify();
		buf_t1 = clock2::now();
		std::cout << "buffer parser stringify time: " << mil(buf_t1-buf_t0).count() << "/ms" << std::endl;
		std::cout << "json:\n" << stringify_pretty_buf << std::endl;
		free(stringify_pretty_buf);
		
		buf_t0 = clock2::now();
		stringify_pretty_buf = doc_buf->stringify_pretty();
		buf_t1 = clock2::now();
		std::cout << "buffer parser stringify pretty time: " << mil(buf_t1-buf_t0).count() << "/ms" << std::endl;
		std::cout << "json:\n" << stringify_pretty_buf << std::endl;
		free(stringify_pretty_buf);
		
		delete buf_parser;
		delete doc_buf;
	
	} catch (jsonP_exception &ex) {
		std::cout << "Parse exception parsing text file: " << ex.what() << std::endl;
		std::cout << "Error snip:\n" << buf_parser->get_error_snip(100, 100) << std::endl;
		delete buf_parser;
		delete doc_buf;
	}

	// sample streaming json from the net by implementing a custom IChunk_reader interface and supplying it to the buffer parser
//	net_chunk_impl *net_reader = nullptr;
//	jsonP_buffer_parser *net_buf_parser = nullptr;
//	jsonP_json *doc_net_buf = nullptr;
//	
//	try {
//		std::cout << "\n**********************************************************\n\n";
//		std::cout << "Starting buffer_parser test with IChunk_reader implementation net_chunk_impl\n";
//		net_reader = new net_chunk_impl{};
//		net_buf_parser = new jsonP_buffer_parser{net_reader, 8192};
//		doc_net_buf = net_buf_parser->parse();
//		char *pretty = doc_net_buf->stringify_pretty();
//		std::cout << pretty << std::endl;
//		free(pretty);
//		
//		delete doc_net_buf;
//		delete net_buf_parser;
//	} catch (jsonP_exception &ex) {
//		std::cout << "Parse exception: " << ex.what() << ", at: " << net_buf_parser->get_error_index() << std::endl;
//		std::cout << "json snippet:\n" << net_buf_parser->get_error_snip(50, 50) << std::endl;
//		
//		delete doc_net_buf;
//		delete net_buf_parser;
//	
//	}


	//sample using the IPush_handler implementation test_push_handler
	std::cout << "\n**********************************************************\n\n";
	std::cout << "Starting push_parser test with IPush_handler implementation test_push_handler\n";
	IPush_handler *handler = new test_push_handler{};
	jsonP_push_parser *push_parser = nullptr;
	
	try {
		push_parser = new jsonP_push_parser{"../samples/sample1.json", handler};
	//	push_parser = new jsonP_push_parser{"/Users/user1/Downloads/large.json", handler};

		auto push_buf_t0 = clock2::now();
		push_parser->parse();
		auto push_buf_t1 = clock2::now();

		std::cout << "Done Parsing with push_parser, parse time: " << mil(push_buf_t1-push_buf_t0).count() << "/ms" << std::endl;

		delete push_parser;
		delete handler;
 
	} catch (jsonP_exception &ex) {
		std::cout << "Parse exception parsing text file: " << ex.what() << std::endl;
		std::cout << "Error snip:\n" << push_parser->get_error_snip(100, 100) << std::endl;
		delete push_parser;
		delete handler;
	}

	return 0;
}



jsonP_json * create_json_doc()
{
	jsonP_json *jsonPjson = new jsonP_json{object, 7, 45, CONVERT_NUMERICS};
	object_id id = jsonPjson->get_doc_root();
	jsonPjson->add_value_type(string, 0, "mykey", (void*)"myVal");
	jsonPjson->add_value_type(string, 0, "mykey_2", (void*)"myVal_2");
	jsonPjson->add_value_type(string, 0, "Amykey_3", (void*)"AmyVal_3");

	long long_val = 87823750023;
	double double_val = -7729355.09723;
	
	object_id new_id = jsonPjson->add_container("new_obj_key", 1, id, object);

	jsonPjson->add_value_type(string, new_id, "NEW_KEY", (void*)"NEW+_VAL");
	jsonPjson->add_value_type(null, new_id, "null_key");
	jsonPjson->add_value_type(numeric_long, new_id, "long_key", &long_val);
	jsonPjson->add_value_type(numeric_double, new_id, "double_key", &double_val);
	jsonPjson->add_value_type(bool_true, new_id, "bool_t_key");
	jsonPjson->add_value_type(bool_false, new_id, "bool_f_key");

	object_id new_id_embed = jsonPjson->add_container("obj_key_embed", 1, new_id, array);
	jsonPjson->add_value_type(string, new_id_embed, NULL, (void*)"myVal");
	jsonPjson->add_value_type(null, new_id_embed, NULL);
	jsonPjson->add_value_type(numeric_long, new_id_embed, NULL, &long_val);

	object_id new_id_embed_embed = jsonPjson->add_container(NULL, 3, new_id_embed, array);
	jsonPjson->add_value_type(string, new_id_embed_embed, NULL, (void*)"myVal");
	jsonPjson->add_value_type(null, new_id_embed_embed, NULL);
	jsonPjson->add_value_type(numeric_long, new_id_embed_embed, NULL, &long_val);

	object_id string_arry = jsonPjson->add_container("string_arry_key", 4, id, array);
	jsonPjson->add_value_type(string, string_arry, NULL, (void*)"val");
	jsonPjson->add_value_type(null, string_arry, NULL, NULL);
	jsonPjson->add_value_type(numeric_long, string_arry, NULL, &long_val);
	jsonPjson->add_value_type(numeric_double, string_arry, NULL, &double_val);
	jsonPjson->add_value_type(bool_true, string_arry, NULL);
	jsonPjson->add_value_type(bool_false, string_arry, NULL);

	object_id string_arry_embed = jsonPjson->add_container(NULL, 2, string_arry, array);
	jsonPjson->add_value_type(string, string_arry_embed, NULL, (void*)"val_");
	jsonPjson->add_value_type(null, string_arry_embed, NULL);

	object_id string_arry_embed_obj = jsonPjson->add_container(NULL, 3, string_arry, object);
	jsonPjson->add_value_type(string, string_arry_embed_obj, "some_key", (void*)"some value");
	jsonPjson->add_value_type(numeric_long, string_arry_embed_obj, "long_key", &long_val);
	jsonPjson->add_value_type(null, string_arry_embed_obj, "null_key");


	return jsonPjson;
}



char * parse_file(std::string f, std::string &json)
{
//	std::ifstream in_file{f};
	std::string line;
	
//	if (!in_file) {
//		std::cerr << "File failed to open" << std::endl;
//		return;
//	}
//	
//	while (std::getline(in_file, line))
//		json += line;
		
	
	FILE *fp = std::fopen(f.c_str(), "r");
	
	if (fp == NULL) {
		std::cerr << "File failed to open" << std::endl;
		return NULL;
	}
	
	struct stat st;
	
	if (stat(f.c_str(), &st) != 0) {
		std::cerr << "failed to fstat file" << std::endl;
		return NULL;
	}
	
	off_t sz = st.st_size;
//	std::cout << "file size: " << sz << std::endl;
	
	char *buf = (char*)malloc(sz+1);
	
//	while (fread((void *)buf, sizeof(char), 4095, fp) > 0) {
//		json += buf;
//	}
	fread((char *)buf, sizeof(char), sz+10, fp);
	buf[sz] = '\0';
	
	fclose(fp);
	
	return buf;
	
//	std::cout << f << ", file size: " << strlen(buf) << std::endl;
	
}

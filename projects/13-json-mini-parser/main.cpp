#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>

enum class JsonType { Null, Bool, Number, String, Array, Object };

class JsonValue {
public:
    JsonType type;
    std::string str_val;
    double num_val;
    bool bool_val;
    std::vector<std::shared_ptr<JsonValue>> arr_val;
    std::map<std::string, std::shared_ptr<JsonValue>> obj_val;
    
    JsonValue(JsonType t) : type(t), num_val(0), bool_val(false) {}
    
    void print(int indent = 0) const {
        std::string spaces(indent * 2, ' ');
        switch (type) {
            case JsonType::Null: std::cout << "null"; break;
            case JsonType::Bool: std::cout << (bool_val ? "true" : "false"); break;
            case JsonType::Number: std::cout << num_val; break;
            case JsonType::String: std::cout << "\"" << str_val << "\""; break;
            case JsonType::Array:
                std::cout << "[\n";
                for (size_t i = 0; i < arr_val.size(); i++) {
                    std::cout << spaces << "  ";
                    arr_val[i]->print(indent + 1);
                    if (i < arr_val.size() - 1) std::cout << ",";
                    std::cout << "\n";
                }
                std::cout << spaces << "]";
                break;
            case JsonType::Object:
                std::cout << "{\n";
                size_t count = 0;
                for (const auto& pair : obj_val) {
                    std::cout << spaces << "  \"" << pair.first << "\": ";
                    pair.second->print(indent + 1);
                    if (++count < obj_val.size()) std::cout << ",";
                    std::cout << "\n";
                }
                std::cout << spaces << "}";
                break;
        }
    }
};

class JsonParser {
    std::string json;
    size_t pos;
    
    void skip_whitespace() {
        while (pos < json.length() && std::isspace(json[pos])) pos++;
    }
    
    std::shared_ptr<JsonValue> parse_value() {
        skip_whitespace();
        if (pos >= json.length()) return nullptr;
        
        char c = json[pos];
        if (c == 'n') return parse_null();
        if (c == 't' || c == 'f') return parse_bool();
        if (c == '"') return parse_string();
        if (c == '[') return parse_array();
        if (c == '{') return parse_object();
        if (c == '-' || std::isdigit(c)) return parse_number();
        
        return nullptr;
    }
    
    std::shared_ptr<JsonValue> parse_null() {
        if (json.substr(pos, 4) == "null") {
            pos += 4;
            return std::make_shared<JsonValue>(JsonType::Null);
        }
        return nullptr;
    }
    
    std::shared_ptr<JsonValue> parse_bool() {
        if (json.substr(pos, 4) == "true") {
            pos += 4;
            auto val = std::make_shared<JsonValue>(JsonType::Bool);
            val->bool_val = true;
            return val;
        }
        if (json.substr(pos, 5) == "false") {
            pos += 5;
            auto val = std::make_shared<JsonValue>(JsonType::Bool);
            val->bool_val = false;
            return val;
        }
        return nullptr;
    }
    
    std::shared_ptr<JsonValue> parse_number() {
        size_t start = pos;
        if (json[pos] == '-') pos++;
        while (pos < json.length() && (std::isdigit(json[pos]) || json[pos] == '.')) pos++;
        
        std::string num_str = json.substr(start, pos - start);
        auto val = std::make_shared<JsonValue>(JsonType::Number);
        val->num_val = std::stod(num_str);
        return val;
    }
    
    std::shared_ptr<JsonValue> parse_string() {
        if (json[pos++] != '"') return nullptr;
        std::string result;
        while (pos < json.length() && json[pos] != '"') {
            if (json[pos] == '\\' && pos + 1 < json.length()) {
                pos++;
                char escaped = json[pos];
                if (escaped == 'n') result += '\n';
                else if (escaped == 't') result += '\t';
                else if (escaped == '\\') result += '\\';
                else if (escaped == '"') result += '"';
                else result += escaped;
            } else {
                result += json[pos];
            }
            pos++;
        }
        if (pos >= json.length()) return nullptr;
        pos++; // Skip closing quote
        
        auto val = std::make_shared<JsonValue>(JsonType::String);
        val->str_val = result;
        return val;
    }
    
    std::shared_ptr<JsonValue> parse_array() {
        if (json[pos++] != '[') return nullptr;
        auto val = std::make_shared<JsonValue>(JsonType::Array);
        skip_whitespace();
        
        if (json[pos] == ']') {
            pos++;
            return val;
        }
        
        while (true) {
            auto elem = parse_value();
            if (!elem) return nullptr;
            val->arr_val.push_back(elem);
            
            skip_whitespace();
            if (json[pos] == ']') {
                pos++;
                break;
            }
            if (json[pos] == ',') {
                pos++;
                continue;
            }
            return nullptr;
        }
        return val;
    }
    
    std::shared_ptr<JsonValue> parse_object() {
        if (json[pos++] != '{') return nullptr;
        auto val = std::make_shared<JsonValue>(JsonType::Object);
        skip_whitespace();
        
        if (json[pos] == '}') {
            pos++;
            return val;
        }
        
        while (true) {
            skip_whitespace();
            auto key = parse_string();
            if (!key) return nullptr;
            
            skip_whitespace();
            if (json[pos++] != ':') return nullptr;
            
            auto value = parse_value();
            if (!value) return nullptr;
            val->obj_val[key->str_val] = value;
            
            skip_whitespace();
            if (json[pos] == '}') {
                pos++;
                break;
            }
            if (json[pos] == ',') {
                pos++;
                continue;
            }
            return nullptr;
        }
        return val;
    }
    
public:
    JsonParser(const std::string& s) : json(s), pos(0) {}
    
    std::shared_ptr<JsonValue> parse() {
        return parse_value();
    }
};

int main() {
    std::cout << "=== JSON Mini Parser ===\n";
    std::cout << "Supports: null, bool, number, string, array, object\n\n";
    
    std::cout << "Enter JSON (single line): ";
    std::string input;
    std::getline(std::cin, input);
    
    JsonParser parser(input);
    auto result = parser.parse();
    
    if (result) {
        std::cout << "\nParsed successfully:\n";
        result->print();
        std::cout << "\n";
    } else {
        std::cout << "Parse error\n";
    }
    
    return 0;
}

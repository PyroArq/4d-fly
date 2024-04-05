
#define StringCastable(Type) template<typename Type, typename =std::enable_if_t<std::is_constructible<std::string,Type>::value > >

class msvc_string {
	char _content[0x10] = "\0"; // this could contain a pointer
	uint64_t _length = 0;  // 0x10
	uint64_t _maxlength = 0x10-1;  // 0x18
	
public:
	constexpr bool isSSO() const {
		return this->_maxlength < 0x10;
	}
	constexpr char* data() {
		if (this->isSSO())
			return this->_content;
		return *reinterpret_cast<char**>(this->_content);
	}
	constexpr const char* data() const {
		if (this->isSSO())
			return this->_content;
		return *reinterpret_cast<char*const*>(this->_content);
	}
	constexpr uint64_t max_size() const { return 0x7fffffffffffffff; }
	constexpr uint64_t   length() const { return this->_length; }
	constexpr uint64_t     size() const { return this->length(); }
	constexpr uint64_t capacity() const { return this->_maxlength; }
	[[nodiscard]] constexpr bool empty() const {
		return this->length();
	}
private:
	constexpr void resize(uint64_t new_maxlength, bool copy = true){
		
		auto newAlloc = ( new_maxlength/0x10 + 1 )*0x10;  // allocate up to next 0x10
		
		if (newAlloc == (this->_maxlength+1))
			return;
		
		char* oldstr = this->data();
		char* newstr;
		if (newAlloc <= 0x10)
			newstr = this->_content;
		else
			newstr = new char[newAlloc];
		
		if (oldstr == newstr)
			return;
		
		if (copy)
			memcpy(newstr,oldstr,this->length()+1);
		
		if (!this->isSSO())
			delete[] oldstr;
		
		this->_maxlength = newAlloc - 1;
		if (newAlloc > 0x10)
			*reinterpret_cast<char**>(this->_content) = newstr;
	}
	constexpr void write( const char* str, uint64_t length ) {
		
		if ( length > this->capacity() )
			resize(length,false);
		
		this->_length = length;
		memcpy(this->data(),str,length);
		this->data()[length] = NULL;
	}
	
public:
	const char* c_str() const {
		return this->data();
	}
	constexpr char& operator[](uint64_t index) {
		return this->data()[index];
	}
	constexpr const char& operator[](uint64_t index) const {
		return this->data()[index];
	}
	template<typename... Args> auto at(Args&&... args) const {
		return std::string(*this).at(args...);
	}
	template<typename... Args> constexpr msvc_string& assign(Args&&... args){
		return *this = std::string(*this).assign(args...);
	}
	constexpr void reserve(uint64_t new_cap){
		if (new_cap <= this->capacity())
			return;
		this->resize(new_cap);
	}
	constexpr void shrink_to_fit(){
		this->resize(this->length());
	}
	constexpr void clear(){
		*this = "";
	}
	template<typename... Args> constexpr msvc_string& operator+=(Args&&... args){
		return *this = std::string(*this).operator+=(args...);
	}
	
	
	constexpr operator std::string() const {
		return *new std::string(this->data());
	}
	constexpr ~msvc_string(){
		if (!this->isSSO())
			delete[] this->data();
	}
	constexpr msvc_string(){}
	constexpr msvc_string(const msvc_string& str) {
		this->write(str.data(),str.length());
	}
	constexpr msvc_string(const std::string str) {
		this->write(str.data(),str.length());
	}
	// cast all other stuff to std::string, let it do the main work
	StringCastable(String) constexpr msvc_string(const String& rawstr){
		std::string str = rawstr;
		this->write(str.data(),str.length());
	}
	
	constexpr msvc_string& operator=(const msvc_string& str){
		this->write(str.data(),str.length());
		return *this;
	}
};

// we are gonna use a bunch of constexpr which may or may not actually compile to constexpr, so we supress the warnings about that
// we could duplicate all the functions and do it properly, but ¯\_(ツ)_/¯
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-constexpr"

constexpr auto operator+(const msvc_string& str1, const msvc_string& str2){
	return (std::string) str1 + (std::string) str2;
}
StringCastable(String) constexpr auto operator+(const msvc_string& str1, const String str2){
	return (std::string) str1 + (std::string) str2;
}
StringCastable(String) constexpr auto operator+(const String str1, const msvc_string& str2){
	return (std::string) str1 + (std::string) str2;
}

constexpr auto operator==(const msvc_string& str1, const msvc_string& str2){
	return (std::string) str1 == (std::string) str2;
}
StringCastable(String) constexpr auto operator==(const msvc_string& str1, const String str2){
	return (std::string) str1 == (std::string) str2;
}
StringCastable(String) constexpr auto operator==(const String str1, const msvc_string& str2){
	return (std::string) str1 == (std::string) str2;
}

constexpr auto operator<=>(const msvc_string& str1, const msvc_string& str2){
	return (std::string) str1 <=> (std::string) str2;
}
StringCastable(String) constexpr auto operator<=>(const msvc_string& str1, const String str2){
	return (std::string) str1 <=> (std::string) str2;
}
StringCastable(String) constexpr auto operator<=>(const String str1, const msvc_string& str2){
	return (std::string) str1 <=> (std::string) str2;
}

#pragma GCC diagnostic pop

std::ostream& operator<<( std::ostream& os, const msvc_string& str ){
	return os << str.data();
}

std::istream& operator>>( std::istream& is, msvc_string& str ){
	std::string capture;
	is >> capture;
	str = capture;
	return is;
}

template<> struct std::hash<msvc_string> {
    auto operator()(msvc_string const& s) const noexcept {
        return std::hash<std::string>{}(s);
    }
};
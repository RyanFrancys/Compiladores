#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Node {
protected: 
    vector<Node*> children;

public:
    virtual string toStr(){
        return "stmts";
    }
    void append(Node *n) {
        children.push_back(n);
    }
    vector<Node*>& getChildren() {
        return children;
    }
};

class Program : public Node {
public:
    virtual string toStr() {
        return "Program";
    }
};

class Inteiro : public Node {
protected:
    int value;
public: 
    Inteiro(const int v) {
        value = v;
    }

    virtual string toStr() override {
        return to_string(value);
    }
};

class Pf : public Node {
protected:
    float value;
public: 
    Pf(const float v) {
        value = v;
    }

    virtual string toStr() override {
        return to_string(value);
    }
};


class Id : public Node {
protected:
    string name;
public: 
    Id(const string n) {
        name = n;
    }

    virtual string toStr() override {
        return name;
    }
};

class Variavel : public Node {
protected:
    string name;
    Node *value;
public: 
    Variavel(const string n, Node *v) {
        name = n;
        value = v;
        children.push_back(v);
    }

    virtual string toStr() override {
        return name + " =";
    }
};

class Unario : public Node {
protected:
    Node *value;
    char operation;

public: 
    Unario(char op, Node *v) {
        value = v;
        operation = op;
        children.push_back(v);
    }

    virtual string toStr() override {
        string aux;
        aux.push_back(operation);
        return aux;
    }
};

class OpBinaria : public Node {
protected:
    Node *value1;
    Node *value2;
    char operation;

public: 
    OpBinaria(Node *v1, char op, Node *v2) {
        value1 = v1;
        value2 = v2;
        operation = op;
        children.push_back(v1);
        children.push_back(v2);
    }

    virtual string toStr() override {
        string aux;
        aux.push_back(operation);
        return aux;
    }
};

class Mostra : public Node{
protected: 
Node *value;

public:
    Mostra(Node *v) {
        value = v;
        children.push_back(v);
    }
    
    virtual string toStr() {
        return "mostra";
    }
};

void printf_tree_recursive(Node *noh) {
    for(Node *c : noh->getChildren()) {
        printf_tree_recursive(c);
    }
    cout << "N" << (long int)noh << "[label=\"" <<
        noh->toStr() << "\"];" << endl;

    // imprime as ligações c/ os filhos
    for(Node *c : noh->getChildren()) {
        cout << "N" << (long int)noh << "--" <<
            "N" << (long int)c << ";" << endl;
    }
}

void printf_tree(Node *root) {
    cout << "graph {" << endl;
    printf_tree_recursive(root);
    cout << "}" << endl;
}

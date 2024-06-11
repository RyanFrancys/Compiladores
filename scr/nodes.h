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

class Boleano : public Node {
protected:
    bool value;
public: 
    Boleano(const bool v) {
        value = v;
    }

    virtual string toStr() override {
        return to_string(value);
    }
};

class Palavra : public Node {
protected:
    string frase;
public: 
    Palavra(const string v) {
        frase = v;
    }

    virtual string toStr() override {
        return frase;
    }
};


class Loop : public Node {
protected:
     Node *value;
public: 
    Loop(Node *v) {
        value = v;
        children.push_back(v);
    }

    virtual string toStr() override {
        return "Loop";
    }
};

class Enquanto : public Node {
protected:
     Node *condition;
     Node *content;
public: 
    Enquanto(Node *c,Node *n) {
        content = n;
        condition = c;
        children.push_back(c);
        children.push_back(n);
    }

    virtual string toStr() override {
        return "Enquanto";
    }
};

class Se : public Node {
protected:
     Node *condition;
     Node *content;
public: 
    Se(Node *c,Node *n) {
        condition = c;
        content = n;
        children.push_back(c);
        children.push_back(n);
    }

    virtual string toStr() override {
        return "Se";
    }
};

class SeSenao : public Node {
protected:
    Node *contentSe;
    Node *contentSenao;
    Node *condition;
public: 
    SeSenao(Node *c,Node *s,Node *sn) {
        condition = c;
        contentSe = s;
        contentSenao= sn;
        children.push_back(c);
        children.push_back(s);
        children.push_back(sn);
    }

    virtual string toStr() override {
        return "Se Senão";
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

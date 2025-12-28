#include <iostream>
#include <vector>
#include <map>

struct Node {
    int id;
    int parentId;
    std::vector<Node> children;

    Node(int id, int parentId) : id(id), parentId(parentId) {}
};

std::vector<Node> buildTree(const std::vector<Node>& flatList) {
    std::vector<Node> rootNodes;
    std::map<int, size_t> idToIndex;


    for (size_t i = 0; i < flatList.size(); ++i) {
        idToIndex[flatList[i].id] = i;
    }


    std::vector<Node> treeNodes = flatList;


    for (int i = flatList.size() - 1; i >= 0; --i) {
        if (flatList[i].parentId == 0) {

            rootNodes.push_back(treeNodes[i]);
        } else {

            int parentId = flatList[i].parentId;
            if (idToIndex.find(parentId) != idToIndex.end()) {
                size_t parentIndex = idToIndex[parentId];
                treeNodes[parentIndex].children.insert(treeNodes[parentIndex].children.begin(), treeNodes[i]);
            } else {
                std::cerr << "Родительский  id" << parentId << " не найден с  id " << flatList[i].id << std::endl;

                rootNodes.push_back(treeNodes[i]);
            }
        }
    }

    return rootNodes;
}

// Функция для вывода дерева (для отладки)
void printTree(const std::vector<Node>& tree, int indent = 0) {
    for (const auto& node : tree) {
        for (int i = 0; i < indent; ++i) {
            std::cout << "  ";
        }
        std::cout << "id: " << node.id << ", parentId: " << node.parentId << std::endl;
        printTree(node.children, indent + 1);
    }
}


int main() {
    std::vector<Node> flatList = {
            Node(1, 0),
            Node(2, 0),
            Node(3, 1),
            Node(4, 1),
            Node(5, 2),
            Node(6, 4),
            Node(7, 5)
    };

    std::vector<Node> tree = buildTree(flatList);

    printTree(tree);

    return 0;
}
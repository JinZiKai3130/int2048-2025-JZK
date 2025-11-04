#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// 函数：比较两个文件并输出不同的行
bool compareFiles(const string& file1, const string& file2) {
    ifstream f1(file1);
    ifstream f2(file2);
    
    // 检查文件是否成功打开
    if (!f1.is_open()) {
        cerr << "错误：无法打开文件 " << file1 << endl;
        return false;
    }
    if (!f2.is_open()) {
        cerr << "错误：无法打开文件 " << file2 << endl;
        return false;
    }
    
    string line1, line2;
    int lineNum = 0;
    bool filesAreIdentical = true;
    int diffCount = 0;
    const int MAX_DIFFS_TO_SHOW = 5;
    
    // 逐行比较文件
    while (true) {
        bool hasLine1 = (bool)getline(f1, line1);
        bool hasLine2 = (bool)getline(f2, line2);
        lineNum++;
        
        // 如果两个文件都读取完毕，退出循环
        if (!hasLine1 && !hasLine2) {
            break;
        }
        
        // 检查当前行是否不同
        if (hasLine1 != hasLine2 || (hasLine1 && hasLine2 && line1 != line2)) {
            filesAreIdentical = false;
            diffCount++;
            
            // 只显示前5个不同的地方
            if (diffCount <= MAX_DIFFS_TO_SHOW) {
                cout << "第 " << lineNum << " 行不同：" << endl;
                cout << "文件1: " << (hasLine1 ? line1 : "[文件结束]") << endl;
                cout << "文件2: " << (hasLine2 ? line2 : "[文件结束]") << endl;
                cout << "----------------------------------------" << endl;
            }
        }
    }
    
    f1.close();
    f2.close();
    
    // 输出统计信息
    if (!filesAreIdentical) {
        cout << "显示前 " << min(MAX_DIFFS_TO_SHOW, diffCount) << " 个不同之处" << endl;
        cout << "总共有 " << diffCount << " 行不同" << endl;
    }
    
    return filesAreIdentical;
}

// 函数：比较文件并显示统计信息
void compareFilesWithStats(const string& file1, const string& file2) {
    cout << "正在比较文件..." << endl;
    cout << "文件1: " << file1 << endl;
    cout << "文件2: " << file2 << endl;
    cout << "========================================" << endl;
    
    if (compareFiles(file1, file2)) {
        cout << "✓ 两个文件完全相同！" << endl;
    } else {
        cout << "✗ 文件存在差异" << endl;
    }
}

int main(int argc, char* argv[]) {
    string file1, file2;
    
    // 通过命令行参数或用户输入获取文件名
    if (argc == 3) {
        file1 = argv[1];
        file2 = argv[2];
    } else {
        cout << "请输入第一个文件名: ";
        cin >> file1;
        cout << "请输入第二个文件名: ";
        cin >> file2;
    }
    
    compareFilesWithStats(file1, file2);
    
    return 0;
}
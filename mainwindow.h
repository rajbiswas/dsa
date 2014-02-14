#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_search_clicked();

    void on_hash_disp_clicked();

    void on_file_disp_clicked();

    void on_exit_clicked();

    void on_search1_clicked();

    void on_hash_disp1_clicked();

    void on_file_disp_2_clicked();

    void on_pushButton_4_clicked();

    void on_import2_clicked();

    void on_search2_clicked();

    void on_hash_disp2_clicked();

    void on_search3_clicked();

    void on_hash_disp3_clicked();

    void on_import3_clicked();

private:
    Ui::MainWindow *ui;
    void extract_file();
    void extract_file1();
    void extract_file2();
    void extract_file3();
    int hash_index(char *s);
    int hash_index1(char *s);
    void insertHash(char s[],int pos);
    void insertHash1(char s[],int pos);
    void insertHash2(char s[],int pos);
    void insertHash3(char s[],int pos);
    void disp();
    void disp1();
    void disp2();
    void disp3();
    void disp_order();
    void disp_order1();
    void search_word(char *s);
    void search_word1(char *s);
    void search_word2(char *s);
    void search_word3(char *s);
    void out_refresh(QString a,int o);
    void out(QString a,int o);
    void outln(QString a,int o);
};

#endif // MAINWINDOW_H

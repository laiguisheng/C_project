#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

// 歌曲节点结构体
typedef struct Song {
    int id;
    char title[100];
    char artist[50];
    char filepath[300];
    struct Song* prev;
    struct Song* next;
} Song;

// 播放列表管理器
typedef struct PlaylistManager{
    Song* head;
    Song* tail;
    Song* current;
    int song_count;
} PlaylistManager;

// 函数声明
void init_playlist_manager(PlaylistManager* manager);                           // 初始化链表
int load_songs_from_file(PlaylistManager* manager, const char* filename);       // 从文件中读取到链表
void add_song(PlaylistManager* manager, const char* title, const char* artist,  
              const char* filepath);// 人工增加音乐
int delete_song_by_title(PlaylistManager* manager, const char* title);                   // 删除指定名字的音乐
int play_song_by_title(PlaylistManager* manager, const char* title);                     // 根据名字播放音乐
void display_playlist(PlaylistManager* manager);                                // 显示播放列表（正向）
void display_playlist_reverse(PlaylistManager* manager);                        // 显示播放列表（反向）
int export_playlist(PlaylistManager* manager, const char* filename);            // 导出歌单
void next_song(PlaylistManager* manager);                                       // 下一首歌
void previous_song(PlaylistManager* manager);                                   // 上一首歌
int play_song_random(PlaylistManager* manager);                                 // 随机播放音乐（非必做）
int insert_song_at(PlaylistManager* manager, int position, const char* title, const char* artist, const char* filepath);    // 向指定位置添加音乐（非必做）
void clear_playlist(PlaylistManager* manager);                                  // 清空播放列表（非必做）
void sort_by_title(PlaylistManager* manager);                                   // 按照歌曲名排序（非必做）


// linux/Mac 版本
// void play_audio(const char* filename) {
//     char command[256];
//     FILE *mp3File = fopen(filename, "rb");
//     if (!mp3File) {
//         printf("无法打开文件 %s\n", filename);
//         return;
//     }
//     else{
//         printf("Founded File!!");
//     }
//     snprintf(command, sizeof(command), "afplay \"%s\"", filename);
//     int ret = system(command);
//     if (ret != 0) {
//         printf("播放失败或中断，请检查文件格式是否支持。\n");
//     }
// }

// Windows 版本
// void play_audio(const char* filename){
//     char command[256];
//     FILE *mp3File = fopen(filename, "rb");
//     if (!mp3File) {
//         printf("无法打开文件 %s\n", filename);
//         return;
//     }
//     else{
//         printf("Founded File!!");
//     }
//     snprintf(command, sizeof(command), "start \"\" \"%s\"", filename);
//     int ret = system(command);
//     if (ret != 0) {
//         printf("播放失败或中断，请检查文件格式是否支持。\n");
//     }
    
//     // 或者使用 Windows Media Player
//     // sprintf(command, "wmplayer \"%s\"", filename);
//     // system(command);
// }

void play_audio(const char* filename){
    printf("Playing %s ...\n", filename);
}

// 初始化播放管理器
void init_playlist_manager(PlaylistManager* manager){
    manager->head = NULL;
    manager->tail = NULL;
    manager->current = NULL;
    manager->song_count = 0;
}

// 从文件读取内容构建双向链表
int load_songs_from_file(PlaylistManager* manager, const char* filename) {
    FILE* list=fopen(filename,"r");
    if(list==NULL){
        printf("无法打开文件\n");
        return 0;
    }
    char store[1000];
    int loadsong=0;
    while(fgets(store,sizeof(store),list)!=NULL){
        size_t len=strlen(store);
        while(len>0&&(store[len-1]=='\n'||store[len-1]=='\r'||store[len-1]==' ')){
            store[--len]='\0';
        }
        if(len==0){
            continue;//跳过空行
        }
        char title[100] = {0};
        char artist[50] = {0};
        char filepath[300] = {0};
        char* token = strtok(store, ",");
        if (token == NULL) continue; 
        strncpy(title, token, sizeof(title)-1);
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(artist, token, sizeof(artist)-1);
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        strncpy(filepath, token, sizeof(filepath)-1);
        add_song(manager, title, artist, filepath);
        loadsong++;
    }
    fclose(list);
    printf("从文件%s成功加载%d首歌曲\n",filename,loadsong);
    return 0;
}

// 1. 在链表末尾添加歌曲
void add_song(PlaylistManager* manager, const char* title, const char* artist, const char* filepath) {
    Song* tailsong=(Song*)malloc(sizeof(Song));
    if(manager->head==NULL){
        manager->head=tailsong;
        manager->current=tailsong;
        manager->tail=tailsong;
        tailsong->prev=NULL;
    }
    else{
        Song* temp=manager->tail;
        manager->tail=tailsong;
        temp->next=tailsong;
        tailsong->prev=temp;
        temp=NULL;
    }
    manager->song_count++;
    tailsong->id=manager->song_count;
    strcpy(tailsong->title,title);
    strcpy(tailsong->artist,artist);
    strcpy(tailsong->filepath,filepath);
    tailsong->next=NULL;
    printf("已添加歌曲：%s - %s\n",tailsong->artist,tailsong->title);
    return;
}

// 2. 按标题删除歌曲
int delete_song_by_title(PlaylistManager* manager, const char* title) {
    if(manager->head==NULL){
        printf("播放列表为空，无法删除歌曲\n");
        return 0;
    }
    else if(manager->song_count==1){
        if(strcmp(manager->head->title,title)==0){
            printf("已删除歌曲: %s - %s (path: %s)\n",
                manager->head->artist,
                manager->head->title,
                manager->head->filepath);
            free(manager->head);
            manager->head=NULL;
            manager->current=NULL;
            manager->song_count--;
            manager->tail=NULL;
        }
        else{
            printf("未找到该歌曲\n");
        }
    }
    else{
        Song* to_delete=manager->head;
        int deleted_count=0;
        while(to_delete!=NULL){
            if(strcmp(to_delete->title,title)==0){
                if(to_delete==manager->head){
                    printf("已删除歌曲: %s - %s (path: %s)\n",
                         to_delete->artist,
                          to_delete->title,
                           to_delete->filepath);
                    if(to_delete==manager->current){
                        manager->current=to_delete->next;
                    }
                    manager->head=to_delete->next;
                    manager->head->prev=NULL;
                    free(to_delete);
                    if(manager->head!=NULL){
                        to_delete=manager->head;
                    }
                    else{
                        to_delete=NULL;
                    }
                    deleted_count++;
                }
                else if(to_delete==manager->tail){
                    printf("已删除歌曲: %s - %s (path: %s)\n",
                         to_delete->artist,
                          to_delete->title,
                           to_delete->filepath); 
                    manager->tail=to_delete->prev;
                    if(to_delete==manager->current){
                        manager->current=manager->tail;
                    }
                    free(to_delete);
                    manager->tail->next=NULL;
                    to_delete=NULL;
                    deleted_count++;
                }
                else if(to_delete==manager->current){
                    printf("已删除歌曲: %s - %s (path: %s)\n",
                         to_delete->artist,
                          to_delete->title,
                           to_delete->filepath);
                    Song* temp=manager->current;
                    manager->current=temp->next;
                    manager->current->prev=temp->prev;
                    temp->prev->next=manager->current;
                    free(to_delete);
                    to_delete=manager->current;
                    deleted_count++;
                }
                else{
                    printf("已删除歌曲: %s - %s (path: %s)\n",
                         to_delete->artist,
                          to_delete->title,
                           to_delete->filepath);
                    Song* temp=to_delete;
                    to_delete=to_delete->next;
                    to_delete->prev=temp->prev;
                    temp->prev->next=to_delete;
                    free(temp);
                    deleted_count++;
                }
            }
            else{
                to_delete=to_delete->next;
            }
        }
        manager->song_count-=deleted_count;
        if(deleted_count>0){
            printf("共删除 %d 首标题为 \"%s\" 的歌曲\n", deleted_count, title);
        }
        else{
            printf("未找到标题为 \"%s\" 的歌曲\n", title);
        }
        to_delete=manager->head;
        int new_id=1;
        while(to_delete!=NULL){
            to_delete->id=new_id;
            new_id++;
            to_delete=to_delete->next;
        }
    }
    return 0;
}

// 3. 播放歌曲
int play_song_by_title(PlaylistManager* manager, const char* title){
    if(manager->head==NULL){
        printf("播放列表为空，无法播放歌曲\n");
    }
    else{
        manager->current=manager->head;
        int founded_count=0;
        while(manager->current!=NULL&&founded_count!=1){
            if(strcmp(manager->current->title,title)==0){
                founded_count=1;
            }
            else{
                manager->current=manager->current->next;
            }
        }
        if(founded_count>0){
            play_audio(manager->current->filepath);
            printf("已播放标题为\"%s\"的歌曲\n",title);
        }
        else{
            printf("未找到标题为\"%s\"的歌曲\n",title);
        }
    }
    return 0;
}

// 4. 显示播放列表（正向遍历）
void display_playlist(PlaylistManager* manager) {
    Song* temp=manager->head;
    printf("\n播放列表(%d 首歌曲)\n",manager->song_count);
    printf("==================================================\n");
    while(temp!=NULL){
        if(manager->song_count==1){
            printf("%3d.%-20s -%-30s\n (%30s)\n 前驱：NULL | 后继：NULL\n",
                temp->id,
                temp->title,
                temp->artist,
                temp->filepath);
            temp=temp->next;
        }
        else if(temp==manager->head){
            printf("%3d.%-20s -%-30s\n (%30s)\n 前驱：NULL | 后继：%s\n",
                temp->id,
                temp->title,
                temp->artist,
                temp->filepath,
                temp->next->title);
            temp=temp->next;
        }
        else if(temp==manager->tail){
            printf("%3d.%-20s -%-30s\n (%30s)\n 前驱：%s | 后继：NULL\n",
                temp->id,
                temp->title,
                temp->artist,
                temp->filepath,
                temp->prev->title);
            temp=temp->next;
        }
        else{
            printf("%3d.%-20s -%-30s\n (%30s)\n 前驱：%s | 后继：%s\n",
                temp->id,
                temp->title,
                temp->artist,
                temp->filepath,
                temp->prev->title,
                temp->next->title);
            temp=temp->next;
        }
    }
    printf("==================================================\n");
    temp=NULL;
    return;
}

// 5. 显示播放列表（反向遍历）
void display_playlist_reverse(PlaylistManager* manager) {
    Song* temp=manager->tail;
    printf("\n播放列表(%d 首歌曲)\n",manager->song_count);
    printf("==================================================\n");
    while(temp!=NULL){
        if(manager->song_count==1){
            printf("%3d.%-20s -%-30s\n (%30s)\n 前驱：NULL | 后继：NULL\n",
                temp->id,
                temp->title,
                temp->artist);
            temp=temp->next;
        }
        else if(temp==manager->head){
            printf("%3d.%-20s -%-30s\n (%30s)\n 前驱：NULL | 后继：%s\n",
                temp->id,
                temp->title,
                temp->artist,
                temp->filepath,
                temp->next->title);
            temp=temp->prev;
        }
        else if(temp==manager->tail){
            printf("%3d.%-20s -%-30s\n (%30s)\n 前驱：%s | 后继：NULL\n",
                temp->id,
                temp->title,
                temp->artist,
                temp->filepath,
                temp->prev->title);
            temp=temp->prev;
        }
        else{
            printf("%3d.%-20s -%-30s\n (%30s)\n 前驱：%s | 后继：%s\n",
                temp->id,
                temp->title,
                temp->artist,
                temp->filepath,
                temp->prev->title,
                temp->next->title);
            temp=temp->prev;
        }
    }
    printf("==================================================\n");
    temp=NULL;
    return;
}

// 6. 将播放列表保存到文件
int export_playlist(PlaylistManager* manager, const char* filename) {
    if(manager->head==NULL){
        printf("播放列表为空，无法保存\n");
    }
    else{
        FILE *list = fopen(filename, "w");
        int saved_count=0;
        Song* temp=manager->head;
        if(list==NULL){
            printf("无法创建文件:%s\n",filename);
        }
        else{
            while(temp!=NULL){
                fprintf(list,"%s,%s,%s\n",
                    temp->title,
                    temp->artist,
                    temp->filepath);
                temp=temp->next;
                saved_count++;
            }
            printf("已保存%d首歌曲到文件:%s\n",saved_count,
                filename);
            fclose(list);
        }
    }
    return 0;
}

// 7. 下一首
void next_song(PlaylistManager* manager) {
    if(manager->head==NULL){
        printf("播放列表为空!\n");
        return;
    }
    else if(manager->current->next==NULL){
        printf("已是最后一首歌曲\n");
    }
    else{
        manager->current=manager->current->next;
        play_audio(manager->current->filepath);
        printf("Founded File!\n");
    }
    return;
}

// 8. 上一首
void previous_song(PlaylistManager* manager) {
    if(manager->head==NULL){
        printf("播放列表为空!\n");
        return;
    }
    else if(manager->current->prev==NULL){
        printf("已是第一首歌曲\n");
    }
    else{
        manager->current=manager->current->prev;
        play_audio(manager->current->filepath);
        printf("Founded File!\n");
    }
    return;
}

// 9. 随机播放歌曲（非必做）
int play_song_random(PlaylistManager* manager) {
    if(manager->head==NULL){
        printf("播放列表为空\n");
    }
    else{
        int randid= rand()%(manager->song_count)+1;
        manager->current=manager->head;
        while(manager->current->id!=randid){
            manager->current=manager->current->next;
        }
        play_audio(manager->current->filepath);
        printf("Founded File!\n");
    }
    return 0;
}

// 10. 在指定位置插入歌曲（非必做）
int insert_song_at(PlaylistManager* manager, int position, const char* title, 
                   const char* artist, const char* filepath) {
    if(position>manager->song_count||position<0){
        printf("无效的位置!有效范围:0 - %d\n",manager->song_count);
        return 1;
    }
    Song* temp=manager->head;
    Song* newsong=(Song*)malloc(sizeof(Song));
    position++;
    if(manager->head==NULL){
        manager->head=newsong;
        manager->current=newsong;
        manager->tail=newsong;
        manager->song_count++;
        strcpy(newsong->artist,artist);
        strcpy(newsong->filepath,filepath);
        newsong->id=position;
        newsong->next=NULL;
        newsong->prev=NULL;
        strcpy(newsong->title,title);
        return 1;
    }
    if(position==manager->song_count){
        manager->tail->next=newsong;
        newsong->prev=manager->tail;
        manager->tail=newsong;
        newsong->next=NULL;
    }
    else if(position==1){
        manager->head=newsong;
        newsong->prev=NULL;
        newsong->next=temp;
    }
    else{
        while(temp->id!=position){
            temp=temp->next;
        }
        temp->prev->next=newsong;
        newsong->prev=temp->prev;
        temp->prev=newsong;
        newsong->next=temp;
    }
    strcpy(newsong->artist,artist);
    strcpy(newsong->filepath,filepath);
    newsong->id=position;
    strcpy(newsong->title,title);
    manager->song_count++;
    temp=manager->head;
    int new_id=1;
    while(temp!=NULL){
        temp->id=new_id;
        new_id++;
        temp=temp->next;
    }
    return 1;
}

// 12. 按歌曲标题排序（非必做）
void sort_by_title(PlaylistManager* manager) {
    if (manager->head == NULL || manager->head->next == NULL) {
        printf("播放列表为空或仅有1首歌曲，无需排序\n");
        return;
    }
    int swapped; //标记是否发生交换
    Song* p; //外层循环指针
    Song* last_sorted = NULL; //标记最后已排序的节点

    do {
        swapped = 0;
        p = manager->head;
        //遍历未排序的节点
        while (p->next != last_sorted) {
            //按标题字典序比较，strcmp返回>0表示p的标题大于p->next的标题
            if (strcmp(p->title, p->next->title) > 0) {
                //交换两个节点的数据
                //交换id
                int temp_id = p->id;
                p->id = p->next->id;
                p->next->id = temp_id;
                //交换标题
                char temp_title[100];
                strcpy(temp_title, p->title);
                strcpy(p->title, p->next->title);
                strcpy(p->next->title, temp_title);
                //交换歌手
                char temp_artist[50];
                strcpy(temp_artist, p->artist);
                strcpy(p->artist, p->next->artist);
                strcpy(p->next->artist, temp_artist);
                //交换文件路径
                char temp_filepath[300];
                strcpy(temp_filepath, p->filepath);
                strcpy(p->filepath, p->next->filepath);
                strcpy(p->next->filepath, temp_filepath);
                swapped = 1;
            }
            p = p->next;
        }
        last_sorted = p;//更新最后已排序的节点
    } while (swapped);
    Song* temp = manager->head;
    int new_id = 1;
    while (temp != NULL) {
        temp->id = new_id++;
        temp = temp->next;
    }
    char current_title[100] = {0};
    if (manager->current != NULL) {
        strcpy(current_title, manager->current->title);
        temp = manager->head;
        while (temp != NULL) {
            if (strcmp(temp->title, current_title) == 0) {
                manager->current = temp;
                break;
            }
            temp = temp->next;
        }
    } else {
        manager->current = manager->head;
    }
    printf("已按标题排序%d首歌曲\n",manager->song_count);
    return;
}

// 销毁整个链表
void clear_playlist(PlaylistManager* manager) {
    Song* current = manager->head;
    while (current != NULL) {
        Song* next = current->next;
        free(current);
        current = next;
    }
    init_playlist_manager(manager);
    printf("播放列表已清空\n");
}


void display_menu() {
    printf("\n");
    printf("链表音乐播放器管理器\n");
    printf("==========================================\n");
    printf("1. 添加歌曲\n");
    printf("2. 删除歌曲 (按标题)\n");
    printf("3. 播放歌曲 (按标题)\n");
    printf("4. 显示播放列表 (正向)\n");
    printf("5. 显示播放列表 (逆向)\n");
    printf("6. 导出歌单\n");
    printf("7. 切换到下一首歌\n");
    printf("8. 切换到上一首歌\n");
    printf("9. 随机播放歌曲(非必做)\n");
    printf("10. 在指定位置添加歌曲(非必做)\n");
    printf("11. 清空播放列表(非必做)\n");
    printf("12. 按照歌曲名排序(非必做)\n");
    printf("0. 退出程序\n");
    printf("==========================================\n");
    printf("请选择操作 (0-12): ");
}

// 清除输入缓冲区
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 获取用户输入的字符串
void get_user_input(char* buffer, int size, const char* prompt) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);

    // 去除换行符
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}

// 主函数 - 交互式程序
int main() {
    PlaylistManager manager;
    init_playlist_manager(&manager);
    load_songs_from_file(&manager,"song_list.txt");
    srand((unsigned int)time(NULL));

    printf("=== 双向链表音乐播放器管理器 ===\n");
    printf("已加载 %d 首示例歌曲\n", manager.song_count);
    manager.current = manager.head;
    int choice;
    char input[100];

    do {
        display_menu();

        if (scanf("%d", &choice) != 1) {
            printf("无效输入，请输入数字\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: {                   // 添加歌曲
                char title[100], artist[50], filepath[300];
                float duration;

                get_user_input(title, sizeof(title), "请输入歌曲标题: ");
                get_user_input(artist, sizeof(artist), "请输入作者: ");
                get_user_input(filepath, sizeof(filepath), "请输入歌曲路径: ");
                clear_input_buffer();

                add_song(&manager, title, artist, filepath);
                break;
            }
            case 2: {                   // 删除歌曲 (按标题)
                char title[100];
                get_user_input(title, sizeof(title), "请输入要删除的歌曲标题: ");
                int res = delete_song_by_title(&manager, title);
                break;
            }
            case 3: {                   // 播放歌曲（按歌曲名）
                char title[100];
                get_user_input(title, sizeof(title), "请输入要播放的歌曲标题: ");
                int res = play_song_by_title(&manager, title);
                break;
            }
            case 4: {                   // 显示播放列表（正向）
                display_playlist(&manager);
                break;
            }
            case 5: {                   // 显示播放列表（逆向）
                display_playlist_reverse(&manager);
                break;
            }
            case 6: {                   // 导出播放列表
                char path2export[300];
                get_user_input(path2export, sizeof(path2export), "请输入要导出的目标文件名: ");
                int res = export_playlist(&manager, path2export);
                break;
            }
            case 7: {                   // 播放下一首歌曲
                next_song(&manager);
                break;
            }
            case 8: {                   // 播放上一首歌曲
                previous_song(&manager);
                break;
            }
            case 9: {                   // 随机播放歌曲(非必做)
                int res = play_song_random(&manager);
                break;
            }
            case 10: {                  // 在指定位置添加歌曲(非必做)
                char title[100], artist[50], filepath[300];
                int position;
                get_user_input(title, sizeof(title), "请输入歌曲标题: ");
                get_user_input(artist, sizeof(artist), "请输入作者: ");
                get_user_input(filepath, sizeof(filepath), "请输入歌曲路径: ");
                printf("请输入歌曲插入位置: ");
                scanf("%d", &position);
                insert_song_at(&manager, position, title, artist, filepath);
                break;
            }
            case 11: {                  // 清空播放列表(非必做)
                clear_playlist(&manager);
                break;
            }
            case 12: {                  // 按照歌曲名排序(非必做)
                sort_by_title(&manager);
                break;
            }
            case 0: // 退出程序
                printf("感谢使用链表音乐播放器管理器!\n");
                break;
            default:
                printf("? 无效选择，请重新输入\n");
                break;
        }

        // 暂停，让用户看到结果
        if (choice != 0) {
            printf("\n按回车键继续...");
            getchar();
        }

    } while (choice != 0);

    // 清理内存
    clear_playlist(&manager);

    return 0;
}
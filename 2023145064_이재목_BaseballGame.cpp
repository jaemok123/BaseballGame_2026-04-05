/* 학번: 2023145064 이름: 이재목 과목명 : C++ 
학과 : 스마트콘텐츠학과 제출일: 2026-04-05 */
#include <iostream>  // cout, cin 사용
#include <cstdlib>   // rand, srand 사용
#include <ctime>     // time(0) 사용
#include <string>    // string, getline 사용

using namespace std; // std:: 생략

void getValidGuess(int guess[4]) {  // 유효한 입력을 받는 함수, guess 배열에 직접 값을 채움
    while (true) {                  // 유효한 입력이 들어올 때까지 무한 반복
        cout << "4자리 입력 (ex: 1 2 3 4 또는 1234) : "; // 입력 안내 출력
        string line;                // 한 줄 입력을 저장할 문자열
        getline(cin, line);         // 한 줄 전체를 문자열로 받음 (공백 포함)

        int count = 0;              // 추출된 숫자 개수
        for (int i = 0; i < (int)line.size() && count < 5; i++) { // 문자열을 한 글자씩 순회, 5개 이상은 읽지 않음
            if (line[i] >= '0' && line[i] <= '9')                  // 현재 문자가 숫자인지 확인
                guess[count++] = line[i] - '0';                    // 문자 '3' -> 숫자 3 으로 변환 후 저장, count 증가
        }

        if (count != 4) {                                    // 추출된 숫자가 4개가 아니면 (3개 이하 or 5개 이상)
            cout << "  [오류] 숫자 4개를 입력해주세요.\n\n"; // 오류 메시지 출력
            continue;                                        // while 처음으로 돌아가 재입력
        }

        bool duplicate = false;          // 중복 여부 플래그
        for (int i = 0; i < 4; i++)      // 첫 번째 숫자부터 순회
            for (int j = i + 1; j < 4; j++)          // 두 번째 숫자부터 순회 (같은 쌍 두 번 비교 방지)
                if (guess[i] == guess[j]) { duplicate = true; break; } // 같은 숫자가 있으면 중복 플래그 true

        if (duplicate) {                                       // 중복이 있으면
            cout << "  [오류] 중복된 숫자가 있습니다.\n\n";    // 오류 메시지 출력
            continue;                                          // while 처음으로 돌아가 재입력
        }

        return; // 여기까지 통과했으면 유효한 입력이므로 함수 종료
    }
}

int main() {
    srand(time(0)); // 현재 시각을 시드로 설정하여 실행마다 다른 랜덤값 생성

    int choice; // 종료/계속 선택값 저장

    do {                         // choice가 0이 아닌 한 게임 반복
        int answer[4];           // 컴퓨터가 생성한 정답 4자리
        bool used[10] = { false }; // 0~9 각 숫자 사용 여부 체크, 전부 false로 초기화

        for (int i = 0; i < 4; i++) {               // 숫자 4개 뽑기
            int num;                                 // 랜덤으로 뽑은 숫자
            do { num = rand() % 10; } while (used[num]); // 0~9 중 랜덤, 이미 쓴 숫자면 다시 뽑음
            answer[i] = num;                         // 정답 배열에 저장
            used[num] = true;                        // 뽑은 숫자 사용됨으로 표시
        }

        int guess[4];    // 플레이어가 입력한 숫자 저장
        int tries = 0;   // 시도 횟수
        bool win = false; // 정답 여부, 4스트라이크면 true로 변경

        cout << "\n------------------------------------------\n"; // 구분선 출력
        cout << "      4자리 숫자 야구 게임 시작\n";              // 게임 시작 메시지
        cout << "------------------------------------------\n";   // 구분선 출력
        cout << "      중복 없는 0~9 숫자 4개\n\n";               // 규칙 안내

        while (!win) {                                            // win이 true가 될 때까지 반복
            cout << "[" << tries + 1 << "번째 시도] ";           // 현재 시도 번호 출력 (tries가 0부터라 +1)
            getValidGuess(guess);                                 // 유효성 검사 포함 입력 받기
            tries++;                                             // 시도 횟수 증가

            int strike = 0, ball = 0;                            // 스트라이크, 볼 초기화
            for (int i = 0; i < 4; i++) {                        // 입력값 4자리 순회
                if (guess[i] == answer[i]) {                     // 숫자와 위치가 모두 같으면
                    strike++;                                     // 스트라이크 증가
                } else {                                         // 위치가 다르면
                    for (int j = 0; j < 4; j++)                  // 정답 전체와 비교
                        if (guess[i] == answer[j]) ball++;       // 숫자만 같으면 볼 증가
                }
            }

            if (strike == 4) {                                        // 스트라이크 4개면 정답
                cout << "\n 정답 four strike!\n";                     // 정답 메시지 출력
                cout << "총 시도 횟수 : " << tries << "번\n";         // 총 시도 횟수 출력
                win = true;                                           // 루프 탈출을 위해 true로 변경
            } else {                                                  // 정답이 아니면
                cout << ">> " << strike << " Strike, " << ball << " Ball\n\n"; // 스트라이크/볼 출력
            }
        }

        cout << "\n--게임기록--\n";                              // 게임 기록 헤더 출력
        cout << "정답    : ";                                    // 정답 레이블 출력
        for (int i = 0; i < 4; i++) cout << answer[i] << " ";  // 정답 4자리 출력
        cout << "\n총 시도 : " << tries << "번\n";              // 총 시도 횟수 출력

        cout << "\n종료[0] / 계속[1~9] : ";       // 종료/계속 안내 출력
        string choiceLine;                        // 입력값을 저장할 문자열
        getline(cin, choiceLine);                 // 한 줄 전체를 문자열로 받음
        choice = (!choiceLine.empty() && choiceLine[0] >= '0' && choiceLine[0] <= '9')
                 ? choiceLine[0] - '0' : 1;      // 첫 글자가 숫자면 변환, 아니면 기본값 1(계속)

    } while (choice != 0); // 0 입력 시 루프 탈출

    cout << "\n게임 종료\n"; // 종료 메시지 출력
    return 0;               // 프로그램 정상 종료
}
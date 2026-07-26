# operating-systems-OS-lab-1

Лабораторная по ОС на C (C23). Тема — **процессы и потоки**: минимальный shell и стенд, запускающий две задачи в потоках или процессах для сравнения этих моделей.

## Компоненты

- **shell** — запуск команд через `vfork`/`execvp`, замер времени (`CLOCK_MONOTONIC`), проброс сигналов в группу дочернего процесса, выход по `exit`.
- **benchmark-starter** — режимы `threads`/`processes`:
  - **benchmark-1** — внешняя сортировка слиянием через временные файлы и min-кучу (нагрузка на I/O);
  - **benchmark-2** — сортировка в памяти + дедупликация (нагрузка на CPU).
- **Python-скрипты** — `inputGenerator.py` (генерация данных), `benchmarkChecker.py` (проверка вывода), `outputCleaner.py` (очистка).

## Сборка и запуск

CMake ≥ 3.26, Clang (C23). На Linux/macOS включены санитайзеры.

```bash
mkdir build && cmake -Bbuild -H. && cmake --build build

python3 inputGenerator.py ./build/benchmark-starter/input.txt
cd build/benchmark-starter && ./benchmark-starter threads 3 3 && cd ../..
python3 benchmarkChecker.py "./build/benchmark-starter"
python3 outputCleaner.py "./build/benchmark-starter/*output.txt"
```

Формат: `./benchmark-starter <threads|processes> <кол-во b1> <кол-во b2>`.

## Инструментарий

`.clang-format`, `.clang-tidy`, dev-контейнер и CI (GitHub Actions): проверка форматирования, сборка, прогон бенчмарков.

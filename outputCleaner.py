import os
import glob

def delete_files_by_pattern(pattern):
    files_to_delete = glob.glob(pattern)

    if not files_to_delete:
        print(f"Файлы по шаблону '{pattern}' не найдены.")
        return

    for file in files_to_delete:
        try:
            os.remove(file)
            print(f"Удалён файл: {file}")
        except Exception as e:
            print(f"Не удалось удалить файл {file}: {e}")

if __name__ == "__main__":
    pattern = "cmake-build-debug/benchmark-starter/*output.txt"
    delete_files_by_pattern(pattern)

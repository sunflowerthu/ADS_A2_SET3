class ArrayGenerator {
private:
    std::random_device rd;
    std::mt19937 gen;

public:
    ArrayGenerator() : gen(rd()) {}

    std::vector<int> generateRandomArray(size_t size) {
        std::vector<int> array(size);
        std::uniform_int_distribution<int> dis(0, 6000);

        for (size_t i = 0; i < size; ++i) {
            array[i] = dis(gen);
        }

        return array;
    }

    std::vector<int> generateReverseSortedArray(size_t size) {
        std::vector<int> array = generateRandomArray(size);
        std::sort(array.begin(), array.end(), std::greater<int>());
        return array;
    }

    std::vector<int> generateAlmostSortedArray(size_t size, int swapPairs = 10) {
        std::vector<int> array = generateRandomArray(size);
        std::sort(array.begin(), array.end());

        std::uniform_int_distribution<size_t> indexDis(0, size - 1);

        for (int i = 0; i < swapPairs; ++i) {
            size_t idx1 = indexDis(gen);
            size_t idx2 = indexDis(gen);
            std::swap(array[idx1], array[idx2]);
        }

        return array;
    }

    std::vector<int> getSubarray(const std::vector<int>& source, size_t size) {
        return std::vector<int>(source.begin(), source.begin() + size);
    }
};
find . -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec wc -l {} + | awk '{s+=$1} END {print s}'

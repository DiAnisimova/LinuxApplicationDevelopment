#!/bin/bash

DELAY="${1:-0.1}"

input=$(cat)

declare -A ascii_map
declare -a line_lengths
index=0

while IFS= read -r line; do
    line_lengths+=(${#line})
    for ((i=0; i<${#line}; i++)); do
        ascii_map["$index"]="${line:$i:1}"
        index=$((index + 1))
    done
done <<< "$input"

indexes=($(seq 0 $((index - 1))))

shuffled_indexes=($(printf "%s\n" "${indexes[@]}" | shuf))

tput clear

current_pos=0

while [ "$current_pos" -lt "${#shuffled_indexes[@]}" ]; do
    idx=${shuffled_indexes[$current_pos]}

    row=0
    cumulative_length=0
    while [ "$idx" -ge "$cumulative_length" ]; do
        cumulative_length=$((cumulative_length + line_lengths[$row]))
        row=$((row + 1))
    done
    row=$((row - 1))
    col=$((idx - (cumulative_length - line_lengths[$row] - 1)))

    tput cup "$row" "$col"

    echo -n "${ascii_map[$idx]}"

    sleep "$DELAY"

    current_pos=$((current_pos + 1))
done

tput cup ${#line_lengths[@]} 0

echo

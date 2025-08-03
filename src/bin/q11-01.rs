use std::{collections::HashMap};

fn sim(termite_map: &HashMap<char, Vec<char>>, old_counts: &mut HashMap<char, i64>, days: i32) -> i64 {
    let mut new_counts: HashMap<char, i64> = HashMap::new();

    for _ in 0..days {
        for (termite, val) in old_counts.iter() {
            for child in &termite_map[termite] {
                *new_counts.entry(*child).or_insert(0) += *val;
            }
        }

        std::mem::swap(old_counts, &mut new_counts);
        new_counts.clear();
    }
    
    old_counts.values().sum()
}

fn main() {
    let input = std::fs::read_to_string("data.txt").expect("File not found");

    let mut termite_map: HashMap<char, Vec<char>> = HashMap::new();

    for line in input.lines() {
        let parent = line.as_bytes()[0] as char;

        let children: Vec<char> = line[2..]
        .split(',')
        .map(|c| c.chars().next().unwrap())
        .collect();
        
        termite_map.insert(parent, children);
    }

    let mut termite_counts: HashMap<char, i64> = HashMap::new();
    termite_counts.insert('A', 1);

    const DAYS: i32 = 4;

    print!("{}", sim(&termite_map, &mut termite_counts, DAYS));
}   
use std::{collections::HashMap, fs::File, io::{BufRead, BufReader}};

fn sim(termite_map: &HashMap<char, Vec<char>>, termite_counts: &mut HashMap<char, i32>, days: i32) {
    
    for _day in 0..days {
        let mut new_counts: HashMap<char, i32> = HashMap::new();

        for (parent, count) in &mut *termite_counts {
            for child in &termite_map[parent] {
                *new_counts.entry(*child).or_insert(0) += *count;
            } 
        }

        termite_counts.clear();
        std::mem::swap(&mut new_counts, termite_counts);
    }
}   

fn main() {
    let reader = BufReader::new(File::open("data.txt").unwrap());

    let mut termite_map: HashMap<char, Vec<char>> = HashMap::new();
    let mut termite_counts: HashMap<char, i32> = HashMap::new();

    for line in reader.lines() {
        let line = line.unwrap();

        let parent = line.chars().next().unwrap();
        
        let children: Vec<char> = line[2..].split(',').map(|x| x.chars().next().unwrap()).collect();

        termite_map.insert(parent, children);
    }

    termite_counts.insert('A', 1);
    
    let days = 4;  

    sim(&termite_map, &mut termite_counts, days);


    print!("{}", termite_counts.into_values().sum::<i32>());
}
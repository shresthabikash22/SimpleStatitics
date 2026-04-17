
(* stats.ml - Functional implementation using immutable data *)

(* Take the first [n] elements from a list *)
let rec take n lst =
  match (n, lst) with
  | n, _ when n <= 0 -> []
  | _, [] -> []
  | n, x :: xs -> x :: take (n - 1) xs

(* Calculate the mean of a list of integers *)
let calculate_mean (data : int list) : float =
  match data with
  | [] -> 0.0
  | _ ->
      let sum = List.fold_left ( + ) 0 data in
      float_of_int sum /. float_of_int (List.length data)

(* Calculate the median of a list of integers *)
let calculate_median (data : int list) : float =
  match data with
  | [] -> 0.0
  | _ ->
      let sorted = List.sort compare data in
      let len = List.length sorted in
      let mid = len / 2 in
      let median_values =
        sorted
        |> List.mapi (fun i x -> (i, x))
        |> List.filter (fun (i, _) ->
               if len mod 2 = 1 then i = mid
               else i = mid - 1 || i = mid)
        |> List.map snd
      in
      let total = List.fold_left ( + ) 0 median_values in
      float_of_int total /. float_of_int (List.length median_values)

(* Calculate the mode(s) of a list of integers.
   Uses fold_left to build a frequency association list, then filter/map/sort
   to extract modal values — no mutable state anywhere. *)
let calculate_mode (data : int list) : int list =
  match data with
  | [] -> []
  | _ ->
      (* Build frequency table with fold_left: each step either
         increments an existing entry or inserts a fresh one. *)
      let frequencies =
        List.fold_left
          (fun acc x ->
            match List.assoc_opt x acc with
            | Some c -> (x, c + 1) :: List.filter (fun (k, _) -> k <> x) acc
            | None   -> (x, 1) :: acc)
          []
          data
      in
      (* Find the maximum frequency using fold_left *)
      let max_freq =
        List.fold_left (fun acc (_, f) -> max acc f) 0 frequencies
      in
      (* Extract and sort all values that share the maximum frequency *)
      frequencies
      |> List.filter (fun (_, f) -> f = max_freq)
      |> List.map    fst
      |> List.sort   compare

(* Parse space-separated integers from a string *)
let parse_line (line : string) : int list =
  line
  |> String.trim
  |> String.split_on_char ' '
  |> List.filter (fun s -> s <> "")
  |> List.map int_of_string

(* Accumulate numbers from stdin until we have exactly [count] *)
let rec read_numbers_until_count (count : int) (acc : int list) : int list =
  if List.length acc >= count then
    acc |> List.rev |> take count
  else
    try
      let line = input_line stdin in
      let nums = parse_line line in
      read_numbers_until_count count (List.rev_append nums acc)
    with End_of_file ->
      failwith (Printf.sprintf "Expected %d numbers but only got %d"
                  count (List.length acc))

(* Read user input — uses input_line throughout for a single consistent reader *)
let get_user_input () : int list =
  print_string "Enter the number of integers: ";
  flush stdout;

  let count_str = input_line stdin in
  let count =
    try int_of_string (String.trim count_str)
    with Failure _ -> failwith "Invalid integer for count"
  in

  if count <= 0 then
    failwith "Count must be a positive integer"
  else if count > 1_000_000 then
    failwith "Count is too large (max 1,000,000)"
  else begin
    Printf.printf "Enter %d integers separated by spaces or newlines:\n" count;
    flush stdout;
    read_numbers_until_count count []
  end

(* Display results *)
let display_results (original_data : int list) (mean : float)
                    (median : float) (modes : int list) =
  print_endline "\n=== Results ===";

  print_string "Original numbers: ";
  List.iter (fun x -> print_string (string_of_int x ^ " ")) original_data;
  print_newline ();

  Printf.printf "Mean:   %.2f\n" mean;
  Printf.printf "Median: %.2f\n" median;

  print_string "Mode:   ";
  (match modes with
  | [] -> print_string "(no data)"
  | ms when List.length ms = List.length original_data ->
      print_string "(all values appear once)"
  | ms ->
      List.iter (fun x -> print_string (string_of_int x ^ " ")) ms);

  print_newline ()

(* Entry point *)
let main () =
  try
    let numbers = get_user_input () in
    let mean    = calculate_mean   numbers in
    let median  = calculate_median numbers in
    let modes   = calculate_mode   numbers in
    display_results numbers mean median modes;
    exit 0
  with
  | Failure msg ->
      prerr_endline ("Error: " ^ msg);
      exit 1
  | exc ->
      prerr_endline ("Unexpected error: " ^ Printexc.to_string exc);
      exit 1

let () = main ()
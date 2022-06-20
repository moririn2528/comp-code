$arg1=$args[0]
$problem_name=$arg1.Substring($arg1.LastIndexOf("\")+1)
$base_url=$problem_name.Substring(0,$problem_name.IndexOf("_"))
$arg2=$args[1]
$contest_site=$arg2.Substring($arg2.IndexOf("contest\")+8)
$contest_site=$contest_site.Substring(0,$contest_site.IndexOf("\"))
$code_path=$arg2
$test_dir="test/"+$contest_site+"/"+$problem_name
$short_problem_name=$problem_name.Substring($problem_name.LastIndexOf("_")+1)

echo "contest site: $contest_site"
echo "problem name: $problem_name"

switch($contest_site){
    "atcoder" {
        if($base_url.Substring(0,4) -eq "past"){$base_url=$base_url+"-open"}
        $contest_url="https://atcoder`.jp/contests/"+$base_url+"/tasks/"+$problem_name.Replace("-","_")
    }
    "codeforces" {$contest_url="https://codeforces`.com/contest/"+$base_url+"/problem/"+$short_problem_name.ToUpper()}
    "yukicoder" {$contest_url="https://yukicoder`.me/problems/no/"+$short_problem_name}
    "aoj" {$contest_url="https://judge`.u-aizu`.ac`.jp/onlinejudge/description`.jsp?id="+$short_problem_name}
    "codechef" {$contest_url="https://www`.codechef`.com/"+$base_url+"/problems/"+$short_problem_name.ToUpper()}
    default {
        echo "Error: contest site name"
        exit(1)
    }
}


if(-not (Test-Path $test_dir)){
    oj dl -d $test_dir $contest_url
}

g++ -std=c++17 -g -I header -D_GLIBCXX_DEBUG -Wall -Wextra $code_path -o a.exe
oj test -c "./a.exe " -d $test_dir -D
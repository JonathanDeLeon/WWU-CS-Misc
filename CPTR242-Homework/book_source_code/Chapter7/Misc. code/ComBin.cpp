int Combinations(int group, int members)
// Pre: group and members are positive.
// Post: Function value = number of combinations of members size
// that can be constructed from the total group size.
{
    if (members == 1)
        return group;  // Base case 1
    else if (members == group)
        return 1;  // Base case 2
    else
        return (Combinations(group - 1, members - 1) + Combinations(group - 1, members));
}

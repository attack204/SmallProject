class Test {
    public static void main(String []args) {
        Test test = new Test();
        test.run();
    }
    void run() {
        Test a = new Test();
        System.out.println(a.hashCode());
    }
}
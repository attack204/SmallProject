import java.lang.management.ManagementFactory;
import java.lang.management.ThreadInfo;
import java.lang.management.ThreadMXBean;

/**
 * @author attack204
 * date:  2021/10/21
 * email: 757394026@qq.com
 */
public class MultiThread {
    
    public static void main(String[] args) {
        ThreadMXBean threadMxBean = ManagementFactory.getThreadMXBean();
        ThreadInfo[] threadInfos = threadMxBean.dumpAllThreads(false, false);
        for(ThreadInfo threadInfo: threadInfos) {
            System.out.println("[" + threadInfo.getThreadId() + "]" + threadInfo.getThreadName());
        }
    }

}
